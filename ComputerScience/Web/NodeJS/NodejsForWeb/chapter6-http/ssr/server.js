var fs = require("fs");
var http = require("http");

http.createServer((req, res)=>{
    fs.readFile("index.html", (err, data)=>{
        res.writeHead(200, {
            "Content-Type": "text/html"
        });
        res.end(data);
    })
}).listen(3000, ()=>{
    console.log("Server Running at http://localhost:3000");
})