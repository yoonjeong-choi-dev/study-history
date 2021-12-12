const express = require('express');
const jwt = require('jsonwebtoken');
const cors = require('cors');
const url = require('url');

const { verifyToken, apiLimiter } = require('../authMiddleware');
const { Domain, User } = require('../../models');
const { Op } = require('sequelize');

const postRouter = require('./posts');
const userRouter = require('./users');


const router = express.Router();

// CORS 허용 : 등록된 도메인에 대해서만 Access-Control-Allow-Origin 헤더에 추가
router.use(async (req, res, next) => {

    // 등록된 도메인인지 확인
    const domain = await Domain.findOne({
        where: {
            host: url.parse(req.get('origin')).host
        }
    });

    if (domain) {
        cors({
            origin: req.get('origin'),
            credentials: true
        })(req, res, next);
    } else {
        next();
    }
});

router.post('/token', apiLimiter, async (req, res) => {
    // 등록된 도메인 정보에서 클라이언트 비밀키 가져오기
    //const { clientSecret, frontSecret } = req.body;
    const clientSecret = req.body.clientSecret || null;
    const frontSecret = req.body.frontSecret || null;

    
    // 클라이언트 비밀키 검증
    try {
        const domain = await Domain.findOne({
            
            where: {
                [Op.or]: [{clientSecret}, {frontSecret}]
            },
            include: {
                model: User,
                attributes: ['nick', 'id']
            }
        });

        if (!domain) {
            return res.status(401).json({
                code: 401,
                message: 'Non-registered Domain. Please register a domain'
            });
        }
        
        // 등록된 도메인에 한해서 토큰 발행
        const token = jwt.sign({
            id: domain.User.id,
            nick: domain.User.nick,
            type: domain.type
        }, process.env.JWT_SECRET, {
            expiresIn: '30m', // 유효 기간 30분
            issuer: 'yj-api-server'
        });

        // 사용한 비밀키 검증용 코드
        const from = (clientSecret) ? 'Backend' : 'Frontend'

        return res.json({
            code: 200,
            message: `${from} : JWT is issued`,
            token
        });
    } catch (error) {
        console.error(error);
        return res.status(500).json({
            code: 500,
            message: 'Fail to issue a token'
        });
    }
});

router.get('/test', verifyToken, apiLimiter, (req, res) => {
    res.json(req.decoded);
});

router.use('/posts', postRouter);
router.use('/user', userRouter);

module.exports = router;