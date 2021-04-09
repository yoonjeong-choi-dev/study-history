var http = require("http");
var fs = require("fs");
var socketio = require("socket.io");


// Create Server
var server = http.createServer((req, res) => {
    fs.readFile(__dirname + "/index.html", (err, data) => {
        res.writeHead(200, { "Content-Type": "text/html" });
        res.end(data);
    })
}).listen(3000, () => {
    console.log("Server running at http://localhost:3000");
})



// Create Socket
var io = socketio.listen(server);
io.sockets.on("connection", (socket) => { 
    
    // message 이벤트 : 특정 클라이언트가 채팅을 치면, 해당 채팅을 모든 유저에게 전송
    socket.on("message", (data)=>{
        io.sockets.emit("message", data);
    });

    
});