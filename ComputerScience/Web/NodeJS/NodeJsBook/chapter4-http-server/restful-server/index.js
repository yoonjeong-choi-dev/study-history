const http = require('http');
const fs = require('fs').promises;

const localUsers = {};  // local database

const notFound = (res) => {
    res.writeHead(404);
    return res.end('NOT FOUND');
}

const server = http.createServer(async (req, res) => {
    try {
        const { method, url } = req;
        if (method === 'GET') {
            if (url === '/') {
                const page = await fs.readFile('./front-end/index.html');
                res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
                return res.end(page);
            } else if (url === '/about') {
                const page = await fs.readFile('./front-end/about.html');
                res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
                return res.end(page);
            } else if (url === '/users') {
                res.writeHead(200, { 'Content-Type': 'application/json; charset=utf-8' });
                return res.end(JSON.stringify(localUsers));
            } else if (url.startsWith('/front-end/')) {
                // 프론트엔드 리소스 로드
                const data = await fs.readFile(`.${url}`);
                console.log(`Front-end data : ${url}`);
                return res.end(data);
            }
            else {
                return notFound(res);
            }

        } else if (method === 'POST') {
            if (url === '/user') {
                // body에서 데이터 추출
                let body = '';
                req.on('data', (data) => {
                    body += data;
                });

                // body에서 데이터 모두 추출 후 요청 처리
                return req.on('end', () => {
                    console.log('Body data : ', body);
                    const { name } = JSON.parse(body);
                    const id = Date.now();
                    localUsers[id] = name;

                    res.writeHead(200, { 'Content-Type': 'text/plain; charset=utf-8' });
                    res.end("Success to Create");
                });
            } else {
                return notFound(res);
            }

        } else if (method === 'PUT') {
            if (url.startsWith('/user/')) {
                // url 쿼리 스트링에서 key 추출
                const key = url.split('/')[2];

                // body에서 데이터 추출
                let body = '';
                req.on('data', (data) => {
                    body += data;
                });

                // body에서 데이터 모두 추출 후 요청 처리
                return req.on('end', () => {
                    console.log('Body data : ', body);
                    const { name } = JSON.parse(body);
                    localUsers[key] = name;

                    res.writeHead(200, { 'Content-Type': 'text/plain; charset=utf-8' });
                    res.end('Success to Update');
                });
            } else {
                return notFound(res);
            }
        } else if (method === 'DELETE') {
            if (url.startsWith('/user/')) {
                // url 쿼리 스트링에서 key 추출
                const key = url.split('/')[2];
                delete localUsers[key];
                res.writeHead(200, { 'Content-Type': 'text/plain; charset=utf-8' });
                res.end('Success to Delete');
                
            } else {
                return notFound(res);
            }

        } else {    // Client Error
            console.error(err);
            res.writeHead(404, { 'Content-Type': 'text/plain; charset=utf-8' });
            return res.end(err.message);
        }
        // Server Error
    } catch (err) {
        console.error(err);
        res.writeHead(500, {
            'Content-Type': 'text/plain; charset=utf-8'
        });
        res.end(err.message);
    }
});

// 서버 오픈
const port = 8080;
server.listen(port, () => {
    console.log(`Listen localhost:${port}`);
});

// 에러 처리
server.on('error', (error) => {
    console.error(`Fail to server : ${error}`);
});