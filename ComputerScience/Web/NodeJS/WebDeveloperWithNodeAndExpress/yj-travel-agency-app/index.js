const express = require('express');
const expressHandlebars = require('express-handlebars');
const path = require('path');
const fs = require('fs');
const https = require('https'); 
const multiparty = require('multiparty');
const cookieParser = require('cookie-parser');
const expressSession = require('express-session');
const cors = require('cors');
const csrf = require('csurf');
const morgan = require('morgan');

const cluster = require('cluster');

const dotenv = require('dotenv');
dotenv.config();

// 커스텀 미들웨어
const flashMiddleware = require('./lib/middleware/flash');
const cartValidation = require('./lib/middleware/cartValidation');

const app = express();
const port = process.env.PORT || 7166;

// 뷰 엔진 설정
app.engine('handlebars', expressHandlebars({
    // 기본 레이아웃 설정
    defaultLayout: 'defaultLayout',
}));
app.set('view engine', 'handlebars');


// 클러스터 확인 미들웨어
app.use((req, res, next) => {
    if (app.get('env') === 'development') {
        if(cluster.isWorker) {
            console.log(`Worker ${cluster.worker.id} received request`)
        }
    }
    next();
})

// 로그 미들웨어 설정
switch(app.get('env')) {
    case 'development':
        app.use(morgan('dev'));
        break;
    case 'production':
        const logStream = fs.createWriteStream(path.join(__dirname, 'access.log'), {flags: 'a'});
        app.use(morgan('combined', { stream: logStream }));
        break;
};

// 정적 리소스 미들웨어 설정
app.use('/api', cors());    // api 경로에만 cors 적용
app.use(express.static(path.join(__dirname, '/public')));
app.use('/img', express.static(path.join(__dirname, 'uploads')));

// 요청 body 분석 미들웨어 설정
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

// 쿠키 및 세션 쿠키 미들웨어 설정
app.use(cookieParser(process.env.YJ_COOKIE_SECRET));
app.use(expressSession({
    // 요청이 수정되지 않았을 때 강제 저장 여부 : 일반적으로 false 권장
    resave: false,
    // 초기화 되지 않은 새로운 세션 강제 저장 여부 : 일반적으로 false 권장
    saveUninitialized: false,
    // 세션 ID 쿠키 서명에 사용하는 비밀키
    secret: process.env.YJ_COOKIE_SECRET
}));

// body-parser, cookie-parser, express-session 이후에 csurf 설정
app.use(csrf({cookie: true}));
app.use((req, res, next) => {
    // res.locals에 토큰 추가
    res.locals._csrfToken = req.csrfToken();
    next();
})

// 커스텀 미들웨어
app.use(flashMiddleware);

// 라우팅 핸들러 import 및 라우팅 정의
const handler = require('./lib/handlers');

// routing with url
app.get('/', handler.home);
app.get('/about', handler.about);

// mailing service
app.get('/newsletter-signup', handler.newsletterSignup);
app.post('/newsletter-signup/process', handler.newsletterSignupProcess);
app.get('/newsletter-signup/thank-you', handler.newsletterSignupThankYou);
app.get('/newsletter/archive', handler.newsletterSignupResult);

app.get('/newsletter', handler.newsletter);
app.post('/api/newsletter-signup', handler.api.newsletterSignup);

// vaction photo upload
app.get('/contest/vacation-photo', handler.vacationPhotoContest);
app.get('/contest/vacation-photo-thank-you', handler.vacationPhotoContestProcessThankYou);
app.post('/contest/vacation-photo/:year/:month', (req, res) => {
    const form = new multiparty.Form();

    // 요청 데이터를 데이터 필드와 파일로 분석
    form.parse(req, (err, fields, files) => {
        if (err) {
            //res.status(500).send({ error: err.message });
            handler.vacationPhotoContestProcessError(req, res, err);
        }
            
        // files : 파일을 서버의 임시 디렉터리(/tmp)에 저장 후 해당 정보를 배열로 반환
        // fields : 데이터 필드 내용 (application/x-www-form-urlencoded와 다른 바디파서 사용) => req.body로 접근 불가
        handler.vacationPhotoContestProcess(req, res, fields, files);
    })
});

app.get('/contest/vacation-photo-ajax', handler.vacationPhotoContestAjax);
app.post('/api/vacation-photo-contest/:year/:month', (req, res) => {
    const form = new multiparty.Form();

    // 요청 데이터를 데이터 필드와 파일로 분석
    form.parse(req, (err, fields, files) => {
        if (err) {
            handler.api.vacationPhotoContestError(req, res, err);
        }
            
        // files : 파일을 서버의 임시 디렉터리(/tmp)에 저장 후 해당 정보를 배열로 반환
        // fields : 데이터 필드 내용 (application/x-www-form-urlencoded와 다른 바디파서 사용) => req.body로 접근 불가
        handler.api.vacationPhotoContest(req, res, fields, files);
    })
});

// shopping cart
// 카트 관련 세션 초기화 및 데이터 검증 미들웨어 설정
app.use(cartValidation.resetValidation);
app.use(cartValidation.checkWaivers);
app.use(cartValidation.checkGuestCount);

app.get('/shopping-cart', handler.shoppingCart);
app.post('/shopping-cart/add-to-cart', handler.shoppingCartProcess);


// cookie test
app.get('/cookie-test', handler.cookieTest);

// server down test : only for development
app.get('/server-down', (req, res) => {
    if (app.get('env') === 'development') {
        process.nextTick(()=> {
            throw new Error('The server is going to be DOWN');
        });
    } else {
        res.writeHead(200, { 'Content-Type': 'text/html' });
        res.end('<h2>This test is only available in Development Environment</h2>');
    }
    
});


// Custom 404 page
app.use(handler.notFound);

// Custom 500 page
app.use(handler.serverError);

// uncaughtException Handler
process.on('uncaughtException', err => {
    console.error('UNCAUGHT EXCEPTION\n', err.stack);

    // 프로세스 종료 전에 실행해야하는 작업들 수행

    // 작업 종료
    process.exit(1);
})

// https 인증서 설정
const httpsOptions = {
    key: fs.readFileSync(__dirname + '/ssl/yjchoi.pem'),
    cert: fs.readFileSync(__dirname + '/ssl/yjchoi.crt'),
};

const startServer = (port) => {
    // Open the port with https
    https.createServer(httpsOptions, app).listen(port, () => {
        console.log(
            `Express Server started on https://localhost:${port}` +
            ` with ${app.get('env')} mode`);
    });

    // app.listen(port, () => {
    //     console.log(
    //         `Express Server started on http://localhost:${port}` +
    //         ` with ${app.get('env')} mode`);
    // });
}

if (require.main === module) {
    // 노드가 index.js 실행 시 => 포트 열기
    startServer(port);
} else {
    // 다른 경우 => 외부 스크립트에서 import 하기 위해 모듈 export (테스트 용도)
    exports.app = app;
    exports.startServer = startServer;
}
