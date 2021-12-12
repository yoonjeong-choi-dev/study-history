const express = require('express');
const jwt = require('jsonwebtoken');

const { verifyToken, deprecated } = require('../authMiddleware');
const { Domain, User } = require('../../models');

const postRouter = require('./posts');

const router = express.Router();

// 버전 변경
router.use(deprecated);

router.post('/token', async (req, res) => {
    // 등록된 도메인 정보에서 클라이언트 비밀키 가져오기
    const { clientSecret } = req.body;

    // 클라이언트 비밀키 검증
    try {
        const domain = await Domain.findOne({
            where: {clientSecret},
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
            nick: domain.User.nick
        }, process.env.JWT_SECRET, {
            expiresIn: '1m', // 유효 기간 1분
            issuer: 'yj-api-server'
        });

        return res.json({
            code: 200,
            message: 'JWT is issued',
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

router.get('/test', verifyToken, (req, res) => {
    res.json(req.decoded);
});

router.use('/posts', postRouter);

module.exports = router;