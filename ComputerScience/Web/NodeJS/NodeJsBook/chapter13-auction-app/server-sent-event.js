const SSE = require('sse');

module.exports = (server) => {
    // 익스프레스 서버 객체 기반으로 서버센트 이벤트 객체 생성
    const sse = new SSE(server); 

    // 클라이언트와의 연결 이벤트 핸들러 정의
    sse.on('connection', (client) => {
        // 1초에 한번씩 시간 전송
        setInterval(()=> {
            client.send(Date.now().toString());
        }, 1000);
    });
};