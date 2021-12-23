const express = require('express');
const passport = require('passport');
const bcrypt = require('bcrypt');

const { isLoggedIn, isNotLoggedIn } = require('./middlewares/login');

const User = require('../models/user');

const router = express.Router();

router.post('/join', isNotLoggedIn, async (req, res, next) => {
    const { email, nick, password, money } = req.body;

    try {
        // 가입한 유저가 있는지 확인
        const existUser = await User.findOne({ where: { email } });
        if (existUser) {
            return res.redirect('/join?error=exist email');
        }

        // 비밀번호 해싱하여 저장
        const hashed = await bcrypt.hash(password, 12);
        await User.create({
            email,
            nick,
            password: hashed,
            money
        });

        return res.redirect('/');
    } catch (err) {
        next(err);
    }
});

router.post('/login', isNotLoggedIn, (req, res, next) => {
    // passport.authenticate('local') 미들웨어로 로컬 로그인 전략 수행
    passport.authenticate('local', (authError, user, info) => {
        if (authError) {
            return next(authError);
        }
        if (!user) {
            return res.redirect(`/?loginError=${info.message}`);
        }

        return req.login(user, (loginError) => {
            if (loginError) {
                return next(loginError);
            }
            return res.redirect('/');
        })
    })(req, res, next);
});

router.get('/logout', isLoggedIn, (req, res) => {
    req.logout();   // req.user 객체 제거
    req.session.destroy();  // req.session 객체 제거
    res.redirect('/');
});

router.get('/kakao', passport.authenticate('kakao'));

// 카카오 로그인 전략에서 설정한 callurl : 카카오 로그인 후 리다이렉트 되는 주소
// 리다이렉트 후, 다시 카카오 로그인 전략 수행
router.get('/kakao/callback', passport.authenticate('kakao', {
    failureRedirect: '/',
}), (req, res) => {
    res.redirect('/');
});


module.exports = router;