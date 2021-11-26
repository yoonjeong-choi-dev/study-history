const http = require('http');
const fs = require('fs').promises;

const server = http.createServer( async (req, res) => {
    try {
        // 응답 웹 페이지 로드
        const page = await fs.readFile('./index.html');
        // 응답 header & body 작성
        res.writeHead(200, {
            'Content-Type': 'text/html; charset=utf-8'
        });
        res.end(page);
    } catch (err) {
        console.error(err);
        res.writeHead(500, {
            'Content-Type': 'text/plain; charset=utf-8'
        });
        res.end(err.message);
    }
});

// 서버 오픈
server.listen(8080, () => {
    console.log("Listen localhost:8080");
});

// 에러 처리
server.on('error', (error) => {
    console.error(`Fail to server : ${error}`);
});