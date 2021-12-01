var fs = require("fs");
var http = require("http");

http.createServer((req, res)=>{
    fs.readFile("test.jpg", (err, data)=>{
        res.writeHead(200, {
            "Content-Type": "image/jpg"
        });
        res.end(data);
    })
}).listen(3000, ()=>{
    console.log("Server Running at http://localhost:3000");
})


http.createServer((req, res)=>{
    fs.readFile("test.mp3", (err, data)=>{
        res.writeHead(200, {
            "Content-Type": "audio/mp3"
        });
        res.end(data);
    })
}).listen(3001, ()=>{
    console.log("Server Running at http://localhost:3001");
})