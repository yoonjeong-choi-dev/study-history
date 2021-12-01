var express = require("express");
var session = require("express-session");

var app = express();

// 세션 미들웨어 설정
app.use(session({
    secret: "secret key",
    resave: false,
    saveUninitialized: true
}));

app.use((req, res)=>{
    req.session.now = (new Date()).toUTCString();

    res.send(req.session);
})


app.listen(3000, ()=>{
    console.log("Server running at http://localhost:3000");
});