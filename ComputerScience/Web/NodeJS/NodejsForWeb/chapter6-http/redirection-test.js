var http = require("http");

http.createServer((req, res)=>{
    var redirection_url = "http://www.naver.com"
    // 리다이렉션
    res.writeHead(302, {
        "Location": redirection_url
    });

    
    res.end();
}).listen(3000, ()=>{
    console.log("Server Running at http://localhost:3000");
})