const express = require('express');
const axios = require('axios');
const config = require('../config');


const router = express.Router();

// origin 헤더 추가 : 서버에서 CORS 허용 시 사용
axios.defaults.headers.origin = 'http://localhost:8080';

// 토큰 발급을 위한 유틸 함수
const request = async (req, api) => {
    try {
        // 토큰이 없으면 발급 시도
        if (!req.session.jwt) {
            const tokenResult = await axios.post(config.apiHost + '/token', {
                clientSecret: process.env.CLIENT_SECRET
            });

            if (tokenResult.data && tokenResult.data.code == 200) {
                console.log(`Token is issued : ${tokenResult.data.token}`);

                req.session.jwt = tokenResult.data.token;
            } else {
                // 발급 실패 시, 에러 응답 
                return res.json(tokenResult.data);
            }
        }

        // 발급받은 토큰을 이용하여 api 호출
        return await axios.get(config.apiHost + api, {
            headers: {
                authorization: req.session.jwt
            }
        });
    } catch (err) {
        // 토큰 만료시 토큰 재발급 후, 다시 호출
        if (err.response.status === 419) {
            delete req.session.jwt;
            return request(req, api);
        }

        // 이외의 에러
        return err.response;
    }
}

router.get('/mypost', async (req, res, next) => {
    try {
        const result = await request(req, '/posts/my');
        res.json(result.data);
    } catch (err) {
        next(err);
    }
});

router.get('/search/:hashtag', async (req, res, next) => {
    try{
        const result = await request(req, `/posts/hashtag/${encodeURIComponent(req.params.hashtag)}`);
        res.json(result.data);
    } catch (err) {
        next(err);
    }
});

router.get('/friends', async (req, res, next) => {
    try{
        const result = await request(req, '/user');
        res.json(result.data);
    } catch (err) {
        next(err);
    }
});

router.get('/follower', async (req, res, next) => {
    try{
        const result = await request(req, '/user/follower');
        res.json(result.data);
    } catch (err) {
        next(err);
    }
});

router.get('/following', async (req, res, next) => {
    try{
        const result = await request(req, '/user/following');
        res.json(result.data);
    } catch (err) {
        next(err);
    }
});



// jwt 토큰 인증 테스트
router.get('/test', async (req, res, next) => {
    console.log(config.apiHost)
    try {
        // 토큰이 없으면 발급 시도
        if (!req.session.jwt) {
            const tokenResult = await axios.post(config.apiHost + '/token', {
                clientSecret: process.env.CLIENT_SECRET
            });

            if (tokenResult.data && tokenResult.data.code == 200) {
                console.log(`Token is issued : ${tokenResult.data.token}`);

                req.session.jwt = tokenResult.data.token;
            } else {
                // 발급 실패 시, 에러 응답 
                return res.json(tokenResult.data);
            }
        }

        // 발급받은 토큰 테스트
        console.log(`Token : ${req.session.jwt}`);
        const result = await axios.get(config.apiHost + '/test', {
            headers: {
                authorization: req.session.jwt
            }
        });

        return res.json(result.data);
    } catch (err) {
        // 토큰 만료시
        if (err.response.status === 419) {
            return res.json(err.response.data);
        }
        return next(err);
    }
});

// CORS 테스트
router.get('/', (req, res) => {
    res.render('index', {
        apiHost: config.apiHost,
        key: process.env.FRONT_SECRET
    })
})

module.exports = router;