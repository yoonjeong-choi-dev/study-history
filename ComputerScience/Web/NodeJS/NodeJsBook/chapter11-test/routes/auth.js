const express = require('express');
const passport = require('passport');
const bcrypt = require('bcrypt');
const { isLoggedIn, isNotLoggedIn } = require('./authMiddleware');
const User = require('../models/user');

const router = express.Router();

// 회원가입 
router.post('/join', isNotLoggedIn, async(req, res, next) => {
    const { email, nick, password } = req.body;

    try{
        // 가입한 유저가 있는지 확인
        const existUser = await User.findOne({ where: {email}});
        if (existUser) {
            return res.redirect('/join?error=exit');
        }
        
        // 비밀번호 해싱하여 저장
        const hashed = await bcrypt.hash(password, 12);
        await User.create({
            email, nick, 
            password: hashed
        });
        return res.redirect('/');
    } catch (err) {
        console.error('Join : ', err);
        next(err);
    }
});

// 로그인 
router.post('/login', isNotLoggedIn, (req,res,next) => {
    // passport.authenticate('local') 미들웨어로 로컬 로그인 전략 수행
    passport.authenticate('local', (authError, user, info) => {
        if (authError) {
            console.log('Login :', authError);
            return next(authError);
        }
        if(!user) {
            return res.redirect(`/?loginError=${info.message}`)
        }

        // req.login : passport.serializeUser 수행
        // req.login에서 제공하는 user 객체가 serializeUser로 넘어감 
        return req.login(user, (loginError) => {
            if (loginError) {
                console.log(`Login : `, loginError);
                return next(loginError);
            }
            return res.redirect('/');
        })
    })(req, res, next);
});

router.get('/logout', isLoggedIn, (req, res) => {
    console.log('Logout')
    req.logout();   // req.user 객체 제거
    req.session.destroy();  // req.session 객체 제거
    res.redirect('/');
});

// 카카오 로그인 전략 수행
router.get('/kakao', passport.authenticate('kakao'));

// 카카오 로그인 전략에서 설정한 callurl : 카카오 로그인 후 리다이렉트 되는 주소
// 리다이렉트 후, 다시 카카오 로그인 전략 수행
router.get('/kakao/callback', passport.authenticate('kakao', {
  failureRedirect: '/',
}), (req, res) => {
  res.redirect('/');
});


module.exports = router;