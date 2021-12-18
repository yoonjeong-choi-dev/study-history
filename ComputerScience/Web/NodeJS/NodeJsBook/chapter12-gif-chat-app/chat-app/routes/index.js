const express = require('express');
const multer = require('multer');
const path = require('path');
const fs = require('fs');
const ObjectId = require('mongoose').Types.ObjectId;

const Room = require('../schemas/room');
const Chat = require('../schemas/chat');

const router = express.Router();

// 업로드 스토리지 생성
try {
    fs.readdirSync('uploads');
} catch (err) {
    console.log('Create uploads directory');
    fs.mkdirSync('uploads');
}

const upload = multer({
    storage: multer.diskStorage({
        destination(req, file, cb) {
            cb(null, 'uploads/');
        },
        filename(req, file, cb) {
            const ext = path.extname(file.originalname);
            cb(null, path.basename(file.originalname, ext) + Date.now() + ext);
        },
    }),
    limits: { fileSize: 10 * 1024 * 1024 },
});

router.get('/', async (req, res, next) => {
    try {
        // 현재 생성된 모든 방 정보
        const rooms = await Room.find({});

        res.render('index', {
            rooms,
            title: '웹소켓 채팅방',
        });
    } catch (error) {
        next(error);
    }
});

// 채팅방 생성 페이지
router.get('/room', (req, res) => {
    res.render('room', {
        title: '채팅방 생성'
    });
});

// 채팅방 입장
router.get('/room/:id', async (req, res, next) => {
    try {
        const roomId = ObjectId(req.params.id)
        const room = await Room.findOne({ _id: roomId });

        if (!room) {
            return res.redirect('/?error=There is no room');
        }

        if (room.password && room.password !== req.query.password) {
            return res.redirect('/?error=Wrong Password');
        }

        const { rooms } = req.app.get('io').of('/chat').adapter;
        if (rooms && rooms[roomId] && room.max <= rooms[roomId].length) {
            return res.redirect('/?error=Room is Full');
        };

        // 시스템 메시지 생성
        const message = `Enter : ${req.session.color}`
        await Chat.create({
            room: req.params.id,
            user: 'system',
            chat: message,
        });

        const chats = await Chat.find({ room: room._id }).sort('createdAt');

        // 시스템 메시지 전송
        const chat = req.app.get('io').of('/chat')
        chat.to(roomId).emit('join', {
            user: 'system',
            chat: message,
            socket: rooms.adapter
        });

        return res.render('chat', {
            room,
            title: room.title,
            chats,
            user: req.session.color,
        });
    } catch (error) {
        next(error);
    }
});

router.post('/room/:id/exit', async (req, res, next) => {
    const roomId = req.params.id;
    const {message, user} = req.body;
    
    await Chat.create({
        room: roomId,
        user: user,
        chat: message,
    });
    res.send('ok');
})

// 채팅방 생성
router.post('/room', async (req, res, next) => {
    try {
        // 새로운 방 생성
        const newRoom = await Room.create({
            title: req.body.title || '제목없음',
            max: req.body.max || 2,
            owner: req.session.color,
            password: req.body.password
        });

        const io = req.app.get('io');

        // 클라이언트로 방생성 이벤트 전송 => 클라리언트의 채팅방 리스트 업데이트에 사용
        io.of('/room').emit('newRoom', newRoom);

        // 생성된 방으로 리다이렉트
        res.redirect(`/room/${newRoom._id}?password=${req.body.password}`);
    } catch (error) {
        next(error);
    }
});

// 채팅방 삭제
router.delete('/room/:id', async (req, res, next) => {
    try {
        const roomId = req.params.id;
        await Room.remove({ _id: roomId });
        await Chat.remove({ room: roomId });

        setTimeout(() => {
            req.app.get('io').of('/room').emit('removeRoom', roomId);
        })

        res.send('ok');
    } catch (error) {
        next(error);
    }
});

// 이미지 업로드
router.post('/room/:id/gif', upload.single('gif'), async (req, res, next) => {
    try {
        const chat = await Chat.create({
            room: req.params.id,
            user: req.session.color,
            gif: req.file.filename,
        });

        req.app.get('io').of('/chat').to(req.params.id).emit('chat', chat);
        res.send('ok');
    } catch (error) {
        next(error);
    }
})

// 채팅 등록
router.post('/room/:id/chat', async (req, res, next) => {
    try {
        const chat = await Chat.create({
            room: req.params.id,
            user: req.session.color,
            chat: req.body.chat
        });

        req.app.get('io').of('/chat').to(req.params.id).emit('chat', chat);
        res.send('ok');
    } catch (error) {
        next(error);
    }
});

// socket io 간단한 예제
router.get('/example', (req, res) => {
    res.render('socket_example');
});

module.exports = router;