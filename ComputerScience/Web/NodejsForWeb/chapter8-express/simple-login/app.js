var express = require("express");
var fs = require("fs");
var cookieParser = require("cookie-parser");


var app = express();

// Set middlewares
app.use(cookieParser());
app.use(express.urlencoded({extended: false}));

// Route : 로그인 상태에 따라 다르게 라우팅
app.get("/", (req, res)=>{

    // 인증 쿠키가 있는 경우 로그인한 페이지 출력
    if(req.cookies.auth){
        res.send("<h1>Login Success</h1>");
    }
    // 인증 쿠키가 없는 경우 로그인 페이지 리다이렉트
    else{
        res.redirect("/login");
    }
})

// Route : login page
app.get("/login", (req, res)=>{
    fs.readFile(__dirname+"/index.html", (err, data)=>{
        if(err){
            res.writeHead(500, {
                "Content-Type": "text/html"
            });
            res.end("<h1>page not found</h1>");
        }

        res.writeHead(200, {
            "Content-Type": "text/html"
        });
        res.end(data.toString());
    })
})

// Route : Request login
app.post("/login", (req, res)=>{
    var login = req.body.login;
    var pw = req.body.password;

    console.log(login, pw);
    console.log(req.body);

    // 아이디 및 비밀번호 확인
    if(login=="yj" && pw=="1234"){
        // 로그인 성공 시 : 쿠키 생성
        res.cookie("auth", true);
        res.redirect("/");
    }
    else{
        res.redirect("/login");
    }
})


app.listen(3000, ()=>{
    console.log("Server Running at http://localhost:3000");
})