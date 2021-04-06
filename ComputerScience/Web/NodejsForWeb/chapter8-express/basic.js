var express = require("express");

var app = express();

app.use((req, res, next)=>{
    // url 추출
    var name = req.query.name || "Unknown name";
    var region = req.query.region || "Unknown region";

    var ret = "Hello~ " + name+ " from " + region+"~!";
    res.writeHead(200, {"Content-Type": "text/html"});
    res.end(ret);
})

app.listen(3000, ()=>{
    console.log("Server Running at http://localhost:3000");
})