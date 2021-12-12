const express = require('express');
const expressHandlebars = require('express-handlebars');
const path = require('path');

const app = express();
const port = process.env.PORT || 3000;

// 뷰 엔진 설정
app.engine('handlebars', expressHandlebars({
    // 기본 레이아웃 설정
    defaultLayout: 'defaultLayout',
}));
app.set('view engine', 'handlebars');

// 정적 리소스 미들웨어 설정
app.use(express.static(path.join(__dirname, '/public')));

// 라우팅 핸들러 import 및 라우팅 정의
const handler = require('./lib/handlers');

// routing with url
app.get('/', handler.home);

app.get('/about', handler.about);

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
