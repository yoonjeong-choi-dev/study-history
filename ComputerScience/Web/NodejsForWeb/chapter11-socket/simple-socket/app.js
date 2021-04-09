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
    // custom event from client
    socket.on("chatchat", (data)=>{
        console.log("Client Send data : ", data);

        // emit custom event to client
        socket.emit("chat", "Echo: " + data);
    })
});