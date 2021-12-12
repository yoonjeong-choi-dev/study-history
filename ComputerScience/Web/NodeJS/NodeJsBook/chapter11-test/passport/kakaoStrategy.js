const passport = require('passport');
const KakaoStrategy = require('passport-kakao').Strategy;

const User = require('../models/user');

// KakaoStrategy : (전략 설정, 전략 수행 함수)
// 전략 수행 : done 호출 후, passport.authenticate의 콜백함수 수행
module.exports = () => {
    passport.use(new KakaoStrategy({
        clientID: process.env.KAKAO_ID,
        callbackURL: '/auth/kakao/callback',
    }, async (accessToken, refreshToken, profile, done) => {
        console.log('Kakao Profile : ', profile);

        try{
            // 카카오 프로필로 유저가 있는지 확인
            const existUser = await User.findOne({
                where: {snsId: profile.id, provider: 'kakao'}
            });

            // 유저가 있으면 login
            if (existUser) {
                done(null, existUser);
            } else {
                // 카카오 프로필로 유저 등록
                const newUser = await User.create({
                    email: profile._json && profile._json.kakao_account.email,
                    nick: profile.displayName,
                    snsId: profile.id,
                    provider: 'kakao'
                });
                done(null, newUser);
            }
        } catch (err) {
            console.error(`Kakao Login : ${err}`);
            done(error);
        }
    }));
};