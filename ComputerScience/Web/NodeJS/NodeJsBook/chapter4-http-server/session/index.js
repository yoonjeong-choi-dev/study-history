const http = require('http');
const fs = require('fs').promises;
const url = require('url');
const qs = require('querystring');

// 헤더에 있는 쿠키 파싱 함수
const parseCookies = (cookie = '') => {
    return cookie.split(';')
        .map(c => c.split('='))
        .reduce((accumulated, [key, value]) => {
            accumulated[key.trim()] = decodeURIComponent(value);
            return accumulated;
        }, {});
};

// 세션 정보를 저장하는 로컬 변수
const session =  {};

const server = http.createServer(async (req, res) => {
    // 쿠키 파싱
    const cookies = parseCookies(req.headers.cookie);
    console.log('Request Cookies : ', cookies);

    if (req.url.startsWith('/login')) {  // 로그인 페이지
        const { query } = url.parse(req.url);
        const { name } = qs.parse(query);

        // 쿠키 유효 시간을 5m 으로 설정
        const expires = new Date();
        expires.setMinutes(expires.getMinutes() + 5);

        // 세션 정보 저장
        const uniqueId = Date.now();
        session[uniqueId] = {
            name, expires
        };

        // 유효 시간이 있는 쿠키(세션 id)를 헤더에 추가하여 루트 페이지로 리다이렉션
        res.writeHead(302, {
            Location: '/',
            'Set-Cookie': `session=${uniqueId}; Expires=${expires.toGMTString()}; HttpOnly; Path=/`
        });

        res.end();
    } else if (cookies.session && session[cookies.session].expires > new Date()) { // 로그인 한 경우 : 세션 존재
        res.writeHead(200, {
            'Content-Type': 'text/plain; charset=utf-8'
        });
        res.end(`Hello~ ${session[cookies.session].name}`);
    } else { // 로그인 페이지
        try {
            const page = await fs.readFile('./index.html');
            res.writeHead(200, {
                'Content-Type': 'text/html; charset=utf-8'
            });
            res.end(page);
        } catch (err) {
            console.error(err.stack);
            res.writeHead(500, { 'Content-Type': 'text/plain; charset=utf-8' });
            res.end(err.message);
        }
    }
});


const portNumber = 8080;
server.listen(portNumber, () => {
    console.log(`Listen localhost:${portNumber}`)
})