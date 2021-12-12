// 라우팅 핸들러
const fortune = require('./fortune');

exports.home = (req, res) => res.render('index');

exports.about = (req, res) => res.render('about', {
    fortune: fortune.getFortune(),
});

exports.notFound = (req, res) => {
    res.status(404);
    res.render('clientError');
};

// ESLint 와 express 미들웨어 사이의 불일치 => 해당 코드에 대해서는 eslint 무시
/* eslint-disable no-unused-vars */
exports.serverError = (err, req, res, next) => {
    console.log(err.message);

    res.status(500);
    res.render('serverError');
};
/* eslint-disable no-unused-vars */
