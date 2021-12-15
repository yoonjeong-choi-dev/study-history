const express = require('express');
const cookieParser = require('cookie-parser');
const morgan = require('morgan');
const path = require('path');
const session = require('express-session');
const nunjucks = require('nunjucks');
const dotenv = require('dotenv');
const passport = require('passport');
const nocache = require('nocache');
const helmet = require('helmet');
const hpp = require('hpp');
const redis = require('redis');
const RedisStore = require('connect-redis')(session);


dotenv.config();

// radis 클라이언트 객체 생성
const redisClient = redis.createClient({
    url: `redis://${process.env.REDIS_HOST}:${process.env.REDIS_PORT}`,
    password: process.env.REDIS_PASSWORD
})

const pageRouter = require('./routes/page');
const authRouter = require('./routes/auth');
const postRouter = require('./routes/post');
const userRouter = require('./routes/user');
const passportConfig = require('./passport');
const logger = require('./logger');

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
        logger.error(`Fail to connect : ${err}`);
    });

// 미들웨어 설정
if(process.env.NODE_ENV === 'production') {
    app.use(morgan('combined'));
    app.use(helmet({contentSecurityPolicy: false}));
    app.use(hpp());
} else {
    app.use(morgan('dev'));
}
app.use(express.static(path.join(__dirname, 'public')));
app.use('/img', express.static(path.join(__dirname, 'uploads')));
app.use(express.json());
app.use(express.urlencoded({extended: false}));
app.use(cookieParser(process.env.COOKIE_SECRET));

const sessionOption = {
    resave: false,
    saveUninitialized: false,
    secret: process.env.COOKIE_SECRET,
    cookie: {
        httpOnly: true,
        secure: false,
    },
    store: new RedisStore({client: redisClient}),
};

// 배포 환경에서는 프록시 및 쿠키 설정
if (process.env.NODE_ENV === 'production') {
    // https 적용을 위해 서버 앞에 프록시 서버를 두었을 때를 위해서
    sessionOption.proxy = true;

    // 쿠키 설정은 https를 적용할때만 적용
    //cookie.secure = true;
}

app.use(session(sessionOption));
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
    // console.log('===============================================');
    // console.log(err);
    // console.log('===============================================');
    
    logger.info('hello');
    logger.error(err.message);

    res.locals.message = err.message;
    res.locals.error = process.env.NODE_ENV !== 'production' ? err : {};
    res.status(err.status || 500);
    res.render('error');
});


module.exports = app;