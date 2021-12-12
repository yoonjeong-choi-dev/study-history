const express = require('express');
const path = require('path');
const cookieParser = require('cookie-parser');
const passport = require('passport');
const morgan = require('morgan');
const session = require('express-session');
const nunjucks = require('nunjucks');
const dotenv = require('dotenv');

dotenv.config();

const indexRouter = require('./routes');
const authRouter = require('./routes/auth');
const v1 = require('./routes/v1');
const v2 = require('./routes/v2');
const passportConfig = require('./passport');

const app = express();
passportConfig();

app.set('port', process.env.PORT || 8082);

// 템플릿 엔진 설정
app.set('view engine', 'html');
nunjucks.configure('views', {
    express: app,
    watch: true,
});

// DB 연결
const { sequelize } = require('./models');
sequelize.sync({ force: false })
    .then(() => {
        console.log('Success to connect with DB');
    })
    .catch((err) => {
        console.error(`Fail to connect : ${err}`);
    });

// 기본적인 미들웨어 설정
app.use(morgan('dev'));
app.use(express.static(path.join(__dirname, 'public')));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
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

// 인증 미들웨어 설정
app.use(passport.initialize()); // req에 passport 객체 주입
app.use(passport.session());    // req.session 객체에 passport 정보 저장

// 라우터 설정
app.use('/v1', v1);
app.use('/v2', v2);
app.use('/auth', authRouter);
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