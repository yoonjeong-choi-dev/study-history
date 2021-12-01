const express = require('express');
const User = require('../models/user');

const router = express.Router();

router.get('/', async (req, res, next) => {
    try {
        // DB에서 모든 유저 정보 가져와서 렌더링
        const users = await User.findAll();
        res.render('index', {users});
    } catch (err) {
        console.error(err);
        next(err);
    }
});

module.exports = router;