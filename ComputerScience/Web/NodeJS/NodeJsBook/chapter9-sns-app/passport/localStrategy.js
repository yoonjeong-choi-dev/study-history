const passport = require('passport');
const LocalStrategy = require('passport-local').Strategy;
const bcyrpt = require('bcrypt');

const User = require('../models/user');

// LocalStrategy : (전략 설정, 전략 수행 함수)
// 전략 수행 : done 호출 후, passport.authenticate의 콜백함수 수행
module.exports = () => {
    passport.use(new LocalStrategy({
        usernameField: 'email',
        passwordField: 'password'
    }, async (email, password, done) => {
        try{
            // 해당 유저가 있는지 우선 확인
            const existUser = await User.findOne({where: {email}});
            if (existUser) {
                // 패스워드 학인
                const result = await bcyrpt.compare(password, existUser.password);
                if (result) {
                    done(null, existUser);
                } else {
                    // message는 passport.authenticate의 3번째 인자인 info에 해당
                    done(null, false, {message: '비밀번호가 일치하지 않습니다'});
                }
            } else {
                done(null, false, {message: '가입되지 않은 회원입니다'});
            }
        } catch(err) {
            console.log(`Local login : ${err}`);
            done(err);
        }
    }));
};