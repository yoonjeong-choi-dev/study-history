const express = require('express');
const path = require('path');
const morgan = require('morgan');
const cookieParser = require('cookie-parser');
const session = require('express-session');
const passport = require('passport');
const nunjucks = require('nunjucks');
const dotenv = require('dotenv');

dotenv.config();

const indexRouter = require('./routes');
const authRouter = require('./routes/auth');
const passportConfig = require('./passport');

const sse = require('./server-sent-event');
const webSocket = require('./auctionWebsocket');

const {checkAuction} = require('./checkAuctionSheduler');

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
checkAuction(); // 서버 시작 시 경매 상품 확인

// 세션 미들웨어 설정
const sessionMiddleware = session({
    resave: false,
    saveUninitialized: false,
    secret: process.env.COOKIE_SECRET,
    cookie: {
        httpOnly: true,
        secure: false,
    }
});

// 미들웨어 설정
app.use(morgan('dev'));
app.use(express.static(path.join(__dirname, 'public')));
app.use('/img', express.static(path.join(__dirname, 'uploads')));
app.use(express.json());
app.use(express.urlencoded({extended: false}));
app.use(cookieParser(process.env.COOKIE_SECRET));
app.use(sessionMiddleware);

// 인증 미들웨어 : session 설정보다 뒤에 있어야 세션에 인증 정보 추가 가능
app.use(passport.initialize());
app.use(passport.session());

// favicon disable to avoid 404 error
app.get('/favicon.ico', (req, res) => res.status(204));

// 라우터 설정
app.use('/', indexRouter);
app.use('/auth', authRouter);

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

// 웹소켓 및 서버센트 이벤트 설정
webSocket(server, app);
sse(server);