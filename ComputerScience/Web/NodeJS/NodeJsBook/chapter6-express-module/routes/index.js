const express = require('express');

const router = express.Router();


router.get('/', (req, res) => {
    // 세션 등록
    req.session.name = 'yj-local';
    // 비밀 쿠키 설정
    res.cookie('name', 'yjchoi7166', {
        expires: new Date(Date.now() + 90000),
        httpOnly: true,
        secure: true,
        signed: true
    });

    res.render('index', {
        title: 'Express Server',
        host: req.headers.host,
        name: "YJ"
    });
});

module.exports = router;