const http = require('http');
const fs = require('fs');
const port = process.env.PORT || 3000;

const serveStaticFile = (res, path, contentType, responseCode = 200) => {
    fs.readFile(__dirname + path, (err, data) => {
        if (err) {
            res.writeHead(500, {'Content-Type': 'text/plain'});
            return res.end('500 - Internal Server Error');
        }

        res.writeHead(responseCode, {'Content-Type': contentType});
        res.end(data);
    });
};

const server = http.createServer((req, res) => {
    // 쿼리스트링을 무시한 실제 url 추출
    const path = req.url.replace(/\/?(?:\?.*)?$/, '').toLowerCase();
    console.log(`url: ${req.url}\nurl: ${path}\n`)
    switch(path) {
        case '':
            serveStaticFile(res, '/public/index.html', 'text/html');
            break;
        case '/about':
            serveStaticFile(res, '/public/about.html', 'text/html');
            break;
        case '/img/logo.png':
            serveStaticFile(res, '/public/img/logo.png', 'image/png');
            break;
        default:
            serveStaticFile(res, '/public/notFound.html', 'text/html', 404);
            break;
    }
});

server.listen(port, () => {
    console.log(`server started on port ${port}`);
    console.log('Press Ctrl-C to terminate...');
});