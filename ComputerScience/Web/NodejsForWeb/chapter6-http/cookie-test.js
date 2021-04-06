var http = require("http");

http.createServer((req, res)=>{

    // 쿠키 Expires 속성을 위한 변수
    var date = new Date();
    date.setDate(date.getDate()+7);

    // 쿠키 등록
    res.writeHead(200, {
        "Content-Type": "text/html",
        "Set-Cookie": ["breakfast=skip; Expires= " + date.toUTCString(), 
                        "dinner=rice"]
    });

    // 쿠키 출력
    res.end("<h1>" + req.headers.cookie + "</h1>");
}).listen(3000, ()=>{
    console.log("Server Running at http://localhost:3000");
})