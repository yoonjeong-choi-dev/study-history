const jwt = require('jsonwebtoken');
const RateLimit = require('express-rate-limit');

exports.isLoggedIn = (req, res, next) => {
    if (req.isAuthenticated()) {
        next();
    } else {
        res.status(403).send('Need to Login');
    }
};

exports.isNotLoggedIn = (req, res, next) => {
    if(!req.isAuthenticated()) {
        next();
    } else {
        const message = encodeURIComponent('Already Logged In');
        res.redirect(`/?error=${message}`);
    }
};

exports.verifyToken = (req, res, next) => {

    // 비밀키를 이용하여 토큰 검증
    try {
        req.decoded = jwt.verify(req.headers.authorization, process.env.JWT_SECRET);
        return next();
    } catch(err) {
        // 유효 기간 초과인 경우
        if (err.name === 'TokenExpiredError') {
            return res.status(419).json({
                code: 419,
                message: 'Token is expired'
            });
        } 

        return res.status(401).json({
            code: 401,
            message: 'Invalid Token'
        });
    }
};

const apiLimiterFree = new RateLimit({
    windowMs: 60 * 1000,    // 1분
    max: 5,
    handler(req, res) {
        res.status(this.statusCode).json({
            code: this.statusCode,  // 기본값 429,
            message: "Only 5 requests possible per miniute"
        });
    }
});

const apiLimiterPremium = new RateLimit({
    windowMs: 60 * 1000,    // 1분
    max: 10,
    handler(req, res) {
        res.status(this.statusCode).json({
            code: this.statusCode,  // 기본값 429,
            message: "Only 10 requests possible per miniute"
        });
    }
});

exports.apiLimiter = (req, res, next) => {
    //console.log('===================================================');
    //console.log(req.decoded);
    //console.log('===================================================');
    if (req.decoded && req.decoded.type === 'premium') {
        // 프리미엄인 경우
        apiLimiterPremium(req, res, next);
    } else {
        // 무료 or 토큰이 없는 경우
        apiLimiterFree(req, res, next);
    }
}

exports.deprecated = (req, res) => {
    res.status(410).json({
        code: 410,
        message: 'New version is released. Please use new API'
    });
};