const express = require('express');
const path = require('path');
const morgan = require('morgan');
const cookieParser = require('cookie-parser');
const session = require('express-session');
const nunjucks = require('nunjucks');
const dotenv = require('dotenv');
const ColorHash = require('color-hash').default;

dotenv.config();

// 라우터 및 커스텀 모듈 import
const webSocket = require('./chat-socket');
const connect = require('./schemas');
const indexRouter = require('./routes');

const app = express();
app.set('port', process.env.PORT || 8081);

// 템플릿 엔진 설정
app.set('view engine', 'html');
nunjucks.configure('views', {
    express: app,
    watch: true,
});

// mongodb 연결
connect();

// express-session 및 socket.io 공유할 세션 미들웨어 정의
const sessionMiddelware = session({
    resave: false,
    saveUninitialized: false,
    secret: process.env.COOKIE_SECRET,
    cookie: {
        httpOnly: true,
        secure: false,
    },
});

// 미들웨어 설정
app.use(morgan('dev'));
app.use(express.static(path.join(__dirname, 'public')));
app.use('/gif', express.static(path.join(__dirname, 'uploads')));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser(process.env.COOKIE_SECRET));
app.use(sessionMiddelware);

// session id를 이용하여 사용자마다 고유 색상 부여
app.use((req, res, next) => {
    if (!req.session.color) {
        const colorHash = new ColorHash();
        req.session.color = colorHash.hex(req.sessionID);
    }
    next();
});

// favicon disable to avoid 404 error
app.get('/favicon.ico', (req, res) => res.status(204));

// 라우터 설정
app.use('/', indexRouter);

// 에러 처리(400,500)
app.use((req, res, next)=> {
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

const server = app.listen(app.get('port'), () => {
    console.log(`Listen to localhost:${app.get('port')}`);
});

webSocket(server, app, sessionMiddelware);
