var fs = require("fs");
var http = require("http");
var url = require("url");

http.createServer((req, res)=>{
    // url 분석
    var pathname = url.parse(req.url).pathname

    if (pathname=="/" || pathname =="/index"){
        fs.readFile(__dirname+"/index.html", (err, data)=>{
            console.log(__dirname)
            res.writeHead(200, {
                "Content-Type": "text/html"
            });
            res.end(data);
        })
    }
    else if(pathname == "/another"){
        fs.readFile(__dirname+"/other.html", (err, data)=>{
            res.writeHead(200, {
                "Content-Type": "text/html"
            });
            res.end(data);
        })
    }
    else{
        res.writeHead(404);
        res.end();
    }

    
}).listen(3000, ()=>{
    console.log("Server Running at http://localhost:3000");
})