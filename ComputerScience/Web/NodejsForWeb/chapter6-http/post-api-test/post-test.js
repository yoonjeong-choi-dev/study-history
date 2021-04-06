var http = require("http");
var fs = require("fs");

http.createServer((req, res)=>{
    if (req.method=="GET"){
        fs.readFile(__dirname+"/post-test.html", (err, data)=>{
            res.writeHead(200, {"Content-Type": "text/html"});
            res.end(data);
        })
    }
    else if(req.method=="POST"){
        req.on("data", (data)=>{
            res.writeHead(200, {"Content-Type": "text/html"});
            res.end("<h1>" + data+"</h1>");
        })
    }
    

    
}).listen(3000, ()=>{
    console.log("Server Running at http://localhost:3000");
});