const WebSocket = require('ws');
const SocketIO = require('socket.io');
const axios = require('axios');
const cookieParser = require('cookie-parser');
const cookie = require('cookie-signature');

// 웹소켓 네임스페이스 이벤트 핸들러 정의
const onConnectExample = (socket) => {
    const req = socket.request;

    // 클라이언트의 IP를 알아내는 유명한 방법 중 하나
    const ip = req.headers['x-forwarded-for'] || req.connection.remoteAddress;
    console.log('New client connected :', ip, socket.id, req.ip);

    socket.on('disconnect', () => {
        console.log('Client disconnected :', socket.id);
        clearInterval(socket.interval);
    });

    socket.on('error', (error) => {
        console.error(error);
    });

    // 클라이언트 정의 이벤트
    socket.on('reply', (data) => {
        console.log(data, socket.id);
    });

    // 3초마다 클라리언트로 메시지 전송
    socket.interval = setInterval(() => {
        socket.emit('news', 'Hello Socket.io');
    }, 3000);
};

const onConnectRoom = (socket) => {
    console.log('Connected With \'Room\' namespace');

    socket.on('disconnect', () => {
        console.log('Client disconnected from \'Room\':', socket.id);
    });
}

const onConnectChat = (socket) => {
    console.log('Connected With \'Chat\' namespace');

    const req = socket.request;

    // referer : 현재 요청을 보낸 페이지의 주소 => 방 id를 알아낼 수 있음
    const { headers: { referer } } = req;

    // 채팅방 참여시, 클라이언트를 방에 참가 시킴
    // 방 : socket.io에서의 개념으로 동일 방에 있는 소켓끼리만 데이터를 주고 받음
    const roomId = referer.split('/')[referer.split('/').length - 1]
        .replace(/\?.+/, '');
    socket.join(roomId);

    socket.on('disconnect', () => {
        console.log('Client disconnected from \'Chat\':', socket.id);
        socket.leave(roomId);

        // axios 요청에 첨부할 세션 쿠키
        const signedCookie = cookie.sign(req.signedCookies['connect.sid'], process.env.COOKIE_SECRET);
        const connectSID = `${signedCookie}`;

        const curRoom = socket.adapter.rooms[roomId];
        const userCount = curRoom ? curRoom.length : 0;

        // 방에 사람이 0명이면 방 삭제
        if (userCount === 0) {
            axios.delete(`http://localhost:8081/room/${roomId}`, {
                headers: {
                    Cookie: `connect.sid=s%3A${connectSID}`
                }
            })
                .then(() => {
                    console.log(`Success to delete the room ${roomId}`);
                })
                .catch((error) => {
                    console.log(error);
                });
        } else {
            const message = `Leave : ${req.session.color}`
            axios.post(`http://localhost:8081/room/${roomId}/exit`, {
                user : 'system',
                message,
            },
                {
                    headers: {
                        Cookie: `connect.sid=s%3A${connectSID}`
                    }
                })
                .catch((error) => {
                    console.log(error);
                });

            // 시스템 메시지 생성
            socket.to(roomId).emit('exit', {
                user: 'system',
                chat: message,
                // TODO : 전체 사용자 수 및 사용자 정보도 같이 전송 필요
            });
        }
    });
}

module.exports = (server, app, sessionMiddelware) => {
    // 인자로 받은 익스프레스 서버롤 이용하여 소켓 IO 객체 생성
    // path : 클라이언트가 접속해야하는 경로
    const io = SocketIO(server, { path: '/socket.io' });

    // 라우터에서 소켓 객체 사용을 위해 추가
    // 라우터에서 특정 작업에 대한 결과를 웹소켓을 통해 이벤트로 클라이언트로 전달
    app.set('io', io);

    // 네임 스페이스 정의
    const example = io.of('/example');
    const room = io.of('/room');
    const chat = io.of('/chat');

    // 미들웨어 설정
    io.use((socket, next) => {
        // axios 요청 시, 서버에 쿠키 전송
        cookieParser(process.env.COOKIE_SECRET)(socket.request, socket.request.res, next);

        // 세션 미들웨어 설정 : 소켓에서도 세션 정보 사용 하기 위해
        // socket.reqeust 객체에 세션 객체가 생성
        sessionMiddelware(socket.request, socket.request.res, next);
    })

    // 웹 소켓 서버 연결 이벤트 핸들러
    example.on('connection', onConnectExample);
    room.on('connection', onConnectRoom);
    chat.on('connection', onConnectChat);
};