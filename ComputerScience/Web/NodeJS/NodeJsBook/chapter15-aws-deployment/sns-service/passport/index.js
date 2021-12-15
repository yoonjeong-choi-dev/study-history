const passport = require('passport');
const local = require('./localStrategy');
const kakao = require('./kakaoStrategy');
const User = require('../models/user');

module.exports = () => {

    // 로그인 실행 시, req.session에 어떤 데이터를 저장할지 설정
    passport.serializeUser((user, done) => {
        // done : (error, 저장할 데이터)
        done(null, user.id);
    });

    // 매 요청시 실행 : passport.session 미들웨어가 이 메서드 호출
    // serializeUser에서 설정한 데이터를 인자로 받음
    passport.deserializeUser((id, done) => {
        // 세션에 저장된 id를 이용하여 유저 테이블에서 유저 객체 찾아온다
        User.findOne({ 
            where: {id},
            include: [{
                model: User,
                attributes: ['id', 'nick'],
                as: 'Followers',
            }, {
                model: User,
                attributes: ['id', 'nick'],
                as: 'Followings',
            }]
        })
            .then(user => done(null, user)) // req.user에 해당 유저 정보 저장
            .catch(err => done(err));
    });

    local();
    kakao();
}