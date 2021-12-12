const express = require('express');
const cookieParser = require('cookie-parser');
const morgan = require('morgan');
const session = require('express-session');
const nunjucks = require('nunjucks');
const dotenv = require('dotenv');

dotenv.config();

const indexRouter = require('./routes');

const app = express();
app.set('port', process.env.PORT || 8080);

// 템플릿 엔진 설정
app.set('view engine', 'html');
nunjucks.configure('views', {
    express: app,
    watch: true,
});

// 기본적인 미들웨어 설정
app.use(morgan('dev'));
app.use(express.static(__dirname + '/public'));
app.use(cookieParser(process.env.COOKIE_SECRET));
app.use(session({
    resave: false,
    saveUninitialized: false,
    secret: process.env.COOKIE_SECRET,
    cookie: {
        httpOnly: true,
        secure: false,
    }
}));

// 라우터
app.use('/', indexRouter);

// 에러 처리(400,500)
app.use((req, res, next) => {
    const error = new Error(`${req.method} ${req.url} router does not exits`);
    error.status = 404;
    next(error);
});
app.use((err, req, res, next) => {
    console.log('===============================================');
    console.log(err);
    console.log('===============================================');

    res.locals.message = err.message;
    res.locals.error = process.env.NODE_ENV !== 'production' ? err : {};
    res.status(err.status || 500);
    res.render('error');
});

// 서버 시작
app.listen(app.get('port'), () => {
    console.log(`API server started on localhost:${app.get('port')}`);
});