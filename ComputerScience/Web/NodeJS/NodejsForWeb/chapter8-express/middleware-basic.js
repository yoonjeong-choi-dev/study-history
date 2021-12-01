var express = require("express");

var app = express();

app.use((req, res, next)=>{
    res.text = "1st Middleware";
    next();
})

app.use((req, res, next)=>{
    res.text += "<br>2nd Middleware";
    next();
})

app.use((req, res, next)=>{
    // url 추출
    res.text += "<br>3rd Middleware"
    res.send("<h1>" + res.text + "</h1>");
})

app.listen(3000, ()=>{
    console.log("Server Running at http://localhost:3000");
})