var express = require("express");

var app = express();

app.use((req, res)=>{
    // 헤더의 user-agent 추출
    var agent = req.header("User-Agent");

    // 웹페이지에 출력
    res.writeHead(200, {"Content-Type": "text/html"});
    res.end("<h1>" + agent +" </h1>");
})

app.listen(3000, ()=>{
    console.log("Server Running at http://localhost:3000");
})