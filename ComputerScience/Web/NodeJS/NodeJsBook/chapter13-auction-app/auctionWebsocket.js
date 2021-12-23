const SocketIO = require('socket.io');

module.exports = (server, app) => {
    // 인자로 받은 익스프레스 서버롤 이용하여 소켓 IO 객체 생성
    // path : 클라이언트가 접속해야하는 경로
    const io = SocketIO(server, { 'path': '/socket.io'});

    // 라우터에서 io 객체를 사용하기 위해 익스프레스 서버 앱에 설정
    app.set('io', io);

    // 웹소켓 연결 이벤트 핸들러
    io.on('connection', (socket) => {
        const req = socket.request;

        // referer : 현재 요청을 보낸 페이지의 주소 => 경매방 id를 알아낼 수 있음
        const { headers: { referer } } = req;

        // 경매방 참여시, 클라이언트를 방에 참가 시킴
        // 방 : socket.io에서의 개념으로 동일 방에 있는 소켓끼리만 데이터를 주고 받음
        const roomId = referer.split('/')[referer.split('/').length - 1];
        socket.join(roomId);

        // 연결 해제 시, 소켓의 룸에서 내보냄
        socket.on('disconnect', () => {
            socket.leave(roomId);
        });
    });
};