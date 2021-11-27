const express = require('express');
const morgan = require('morgan');   // 요청,응답에 대한 로깅
const cookieParser = require('cookie-parser');
const session = require('express-session');
const dotenv = require('dotenv');   // 환경 변수 관리를 위한 .env 파일 로드
const path = require('path');
const nunjucks = require('nunjucks');

// .env 파일 로드
dotenv.config();

// 라우팅할 라우터 로드
const indexRouter = require('./routes');
const userRouter = require('./routes/users');
const uploadRouter = require('./routes/upload');

// http 모듈이 내장된 서버 생성
const app = express();

// 템플릿 엔진 설정
app.set('view engine', 'html');
nunjucks.configure('views', {
    express: app,
    watch: true
});

// 포트 설정
app.set('port', process.env.PORT || 8081);

// 미들 웨어 설정
app.use(morgan('dev'));     // dev, combined 사용
app.use('/', express.static(path.join(__dirname, 'public')));    // 정적 리소스 경로

// body-parser : 요청의 body를 해석하여 req.body 객체를 만들어주는 미들웨어 설정
app.use(express.json());
app.use(express.urlencoded({ extended : false}));

// 환경 변수에 설정한 비밀키를 이용하여 쿠키 파서 설정 : 비밀키로 쿠키 서명
app.use(cookieParser(process.env.COOKIE_SECRET));

// 사용자별 요청에 세션 객체 유지
app.use(session({
    resave: false,
    saveUninitialized: false,
    secret: process.env.COOKIE_SECRET,
    cookie: {
        httpOnly: true,
        secure: false
    },
    name: 'session-cookie'
}));


// 라우터 설정
app.use('/', indexRouter);
app.use('/user', userRouter);
app.use('/upload', uploadRouter);
app.use((req, res, next) => {
    const error = new Error(`${req.method} ${req.url} router does not eixits`);
    error.status = 404;
    next(error);
});
app.use((err, req, res, next) => {
    res.locals.message = err.message;
    // 배포 환경인 경우는 스택 트레이스 출력 x
    res.locals.error = process.env.NODE_ENV != 'production' ? err : {};
    res.status(err.status || 500);
    res.render('error');
})


app.listen(app.get('port'), () => {
    console.log(`Listen to localhost:${app.get('port')}`);
});