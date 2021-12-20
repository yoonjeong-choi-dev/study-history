const express = require('express');
const expressHandlebars = require('express-handlebars');
const path = require('path');
const multiparty = require('multiparty');

const app = express();
const port = process.env.PORT || 7166;

// 뷰 엔진 설정
app.engine('handlebars', expressHandlebars({
    // 기본 레이아웃 설정
    defaultLayout: 'defaultLayout',
}));
app.set('view engine', 'handlebars');

// 정적 리소스 미들웨어 설정
app.use(express.static(path.join(__dirname, '/public')));

// 요청 body 분석 미들웨어 설정
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

// 라우팅 핸들러 import 및 라우팅 정의
const handler = require('./lib/handlers');

// routing with url
app.get('/', handler.home);
app.get('/about', handler.about);

// mailing service
app.get('/newsletter-signup', handler.newletterSignup);
app.post('/newsletter-signup/process', handler.newletterSignupProcess);
app.get('/newsletter-signup/thank-you', handler.newletterSignupThankYou);

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


// legacy




// Custom 404 page
app.use(handler.notFound);

// Custom 500 page
app.use(handler.serverError);

if (require.main === module) {
    // 노드가 index.js 실행 시 => 포트 열기
    // Open the port
    app.listen(port, () => {
        console.log(`Express Server started on http://localhost:${port}`);
    });
} else {
    // 다른 경우 => 외부 스크립트에서 import 하기 위해 모듈 export (테스트 용도)
    module.exports = app;
}
