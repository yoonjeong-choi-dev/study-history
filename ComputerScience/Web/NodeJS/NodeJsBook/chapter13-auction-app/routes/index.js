const express = require('express');
const Sequelize = require('sequelize');
const schedule = require('node-schedule');

const multer = require('multer');
const path = require('path');
const fs = require('fs');

const { refreshAuction } = require('../checkAuctionSheduler');
const { User, Good, Auction } = require('../models');
const { isLoggedIn, isNotLoggedIn } = require('./middlewares/login');


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


const router = express.Router();


// 최상단 미들웨어
router.use((req, res, next) => {
    // res.locals의 정보들은 템플릿 엔진 전체에서 사용
    // 렌더링을 위한 데이터 설정 후, 다음 미들웨어로 넘김
    res.locals.user = req.user;
    next();
});


// 메인 페이지
router.get('/', async (req, res, next) => {
    try {
        // 모든 입찰되지 않은 경매 상품 출력
        const goods = await Good.findAll({ where: { SoldId: null }});
        res.render('main', {
            title: 'Node Auction',
            goods,
        });
    } catch (err) {
        next(err);
    }
});

// 회원 가입 폼
router.get('/join', isNotLoggedIn, (req, res) => {
    res.render('join', {
        'title': 'Sing Up - Auction',
    });
});

// 상품 등록 폼
router.get('/good', isLoggedIn, (req, res) => {
    res.render('good', {
        title: 'Register Good - Auction',
    });
});

// 상품 등록
router.post('/good', isLoggedIn, upload.single('img'), async (req, res, next) => {
    try {
        const { name, price, duration, description } = req.body;

        const good = await Good.create({
            OwnerId: req.user.id,
            name,
            img: req.file.filename,
            price,
            description: description ,
            duration: duration || 24,
        });
        
        // 경매 마감 시간 계산
        const end = new Date();
        end.setHours(end.getHours() + parseInt(good.duration));
        
        // 스케줄러 생성
        schedule.scheduleJob(end, refreshAuction);

        res.redirect('/');
    } catch (err) {
        next(err);
    }
});

// 경매 방 입장
router.get('/good/:id', isLoggedIn, async (req, res, next) => {
    try {
        // 상품 및 해당 상품에 대한 입찰 내역
        const goodId = req.params.id;
        const [good, auction] = await Promise.all([
            Good.findOne({
                where: { id: goodId },
                include: {
                    model: User,
                    as: 'Owner',
                },
            }),
            Auction.findAll({
                where: { GoodId: goodId },
                include: { model: User },
                order: [['bid', 'ASC']],
            })
        ]);

        res.render('auction', {
            title: `${good.name} - Auction`,
            good,
            auction,
        });
    } catch (err) {
        next(err);
    }
});

// 입찰
router.post('/good/:id/bid', isLoggedIn, async (req, res, next) => {
    try {
        const { bid, msg } = req.body;
        const good = await Good.findOne({
            where: { id: req.params.id },
            include: {
                model: Auction,     
            },
            order: [[{model: Auction}, 'bid', 'DESC']],  // 입찰 최고가 순으로 정렬
            limit: 1,
        });

        if(good.price >= bid) {
            return res.status(403).send('시작 가격보다 높게 입찰해야 합니다');
        }
        if (new Date(good.createAt).valueOf() + (good.duration * 60 * 60 * 1000) < new Date()) {
            return res.status(403).send('경매가 종료 되었습니다');
        }
        if (good.Auctions[0] && good.Auctions[0].bid >= bid) {
            return res.status(403).send('이전 입찰가보다 높아야 합니다');
        }
        if(good.OwnerId === req.user.id) {
            return res.status(403).send('상품 등록자는 입찰할 수 없습니다');
        }

        const result = await Auction.create({
            bid, msg,
            UserId: req.user.id,
            GoodId: req.params.id,
        });

        // 웹소켓으로 입찰 내역 전송
        req.app.get('io').to(req.params.id).emit('bid', {
            bid: result.bid,
            msg: result.msg,
            nick: req.user.nick,
        });

        res.status(200).send('ok');
    } catch (err) {
        return next(err);
    }
});

// 낙찰 내역
router.get('/list', isLoggedIn, async (req, res, next) => {
    try{
        const goods = await Good.findAll({
            where: { SoldId: req.user.id},
            include: { model: Auction},
            order: [[{model: Auction}, 'bid', 'DESC']],
        });

        res.render('list', {title: `낙찰 목록`, goods});
    } catch(err) {
        next(err);
    }
})

module.exports = router;