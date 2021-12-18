const express = require('express');
const path = require('path');
const fs = require('fs').promises;

// 커스텀 웹 소켓 모듈 
const webSocket = require('./chat-socket')

const app = express();
app.set('port', process.env.PORT || 8081);

// 미들웨어 설정
app.use(express.static(path.join(__dirname, 'public')));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));

// favicon disable to avoid 404 error
app.get('/favicon.ico', (req, res) => res.status(204));

// 라우터 설정
app.use('/', async (req, res) => {
    const page = await fs.readFile('./public/index.html');
    res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
    return res.end(page);
});

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

const server = app.listen(app.get('port'), () => {
    console.log(`Listen to localhost:${app.get('port')}`);
});

webSocket(server);
