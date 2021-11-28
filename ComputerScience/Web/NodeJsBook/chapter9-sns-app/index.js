const express = require('express');
const cookieParser = require('cookie-parser');
const morgan = require('morgan');
const path = require('path');
const session = require('express-session');
const nunjucks = require('nunjucks');
const dotenv = require('dotenv');
const passport = require('passport');
const nocache = require('nocache');



dotenv.config();
const pageRouter = require('./routes/page');
const authRouter = require('./routes/auth');
const postRouter = require('./routes/post');
const userRouter = require('./routes/user');
const passportConfig = require('./passport');

const app = express();
passportConfig();
app.set('port', process.env.PORT || 8081);

// 템플릿 엔진 설정
app.set('view engine', 'html');
nunjucks.configure('views', {
    express: app,
    watch: true,
});

// DB 연결
const { sequelize } = require('./models');
sequelize.sync({force: false})
    .then(()=> {
        console.log('Success to connect with DB');
    })
    .catch((err) => {
        console.error(`Fail to connect : ${err}`);
    });

// 미들웨어 설정
app.use(morgan('dev'));
app.use(express.static(path.join(__dirname, 'public')));
app.use('/img', express.static(path.join(__dirname, 'uploads')));
app.use(express.json());
app.use(express.urlencoded({extended: false}));
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
app.use(nocache());

// 인증 미들웨어 설정 : session 설정보다 뒤에서 해야함
app.use(passport.initialize()); // req에 passport 객체 설정
app.use(passport.session());    // req.session 객체에 passport 정보 저장

// 라우팅 설정
app.use('/', pageRouter);
app.use('/auth', authRouter);
app.use('/post', postRouter);
app.use('/user', userRouter);

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

app.listen(app.get('port'), () => {
    console.log(`Listen to localhost:${app.get('port')}`);
});