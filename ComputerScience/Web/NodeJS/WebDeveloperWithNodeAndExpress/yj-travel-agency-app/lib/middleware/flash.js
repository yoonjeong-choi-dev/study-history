// 플래시 메시지 모듈
module.exports = (req, res, next) => {
    // 플래시 메시지가 있으면 세션에서 삭제 후 다음 미들웨어로 전달
    res.locals.flash = req.session.flash;
    delete req.session.flash;

    next();
};