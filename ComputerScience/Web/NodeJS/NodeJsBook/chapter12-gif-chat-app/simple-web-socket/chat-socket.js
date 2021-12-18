const WebSocket = require('ws');

// 웹소켓 이벤트 핸들러 정의

module.exports = (server) => {
    // 인자로 받은 익스프레스 서버롤 이용하여 웹소켓 서버 객체 생성
    const wss = new WebSocket.Server({server});

    // 웹 소켓 서버 연결 이벤트 핸들러
    wss.on('connection', (ws, req) => {
        // 클라이언트의 IP를 알아내는 유명한 방법 중 하나
        const ip = req.headers['x-forwarded-for'] || req.connection.remoteAddress;
        console.log('New client connected :', ip);

        ws.on('message', (message) => {
            console.log(message.toString() + ': ' + ip);
        });

        ws.on('error', (error) => {
            console.error(error);
        });

        ws.on('close', () => {
            console.log('Client disconnected :', ip);
            clearInterval(ws.interval);
        });
        
        // 3초마다 클라리언트로 메시지 전송
        ws.interval = setInterval(() => {
            if (ws.readyState === ws.OPEN) {
                ws.send('Message from server!');
            }
        }, 3000);
    });
};