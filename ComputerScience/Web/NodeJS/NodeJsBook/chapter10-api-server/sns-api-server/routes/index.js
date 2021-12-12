const express = require('express');
const { v4: uuidv4 } = require('uuid');
const { User, Domain } = require('../models');
const { isLoggedIn } = require('./authMiddleware');

const router = express.Router();

// 도메인 등록 페이지
router.get('/', async (req, res, next) => {
    try {

        // 해당 유저가 등록한 domain들을 가져옴(User join with Domain)
        const user = await User.findOne({
            where: {
                id: req.user && req.user.id || null
            },
            include: {model : Domain}
        });

        // 해당 유저 정보 및 도메인 리스트 데이터를 이용한 렌더링
        res.render('login', {
            user, 
            domains: user && user.Domains
        });
    } catch (err) {
        console.log(err);
        next(err);
    }
});

// 도메인 등록
router.post('/domain', isLoggedIn, async (req, res, next) => {
    try {
        await Domain.create({
            UserId: req.user.id,
            host: req.body.host,
            type: req.body.type,
            clientSecret: uuidv4(),
            frontSecret: uuidv4()
        });
        res.redirect('/');
    } catch (err) {
        console.log(err);
        next(err);
    }
});

module.exports = router;