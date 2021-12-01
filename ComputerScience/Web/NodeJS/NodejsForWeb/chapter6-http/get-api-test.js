var http = require("http");
var url = require("url");

http.createServer((req, res)=>{
    var query = url.parse(req.url, true).query;
    
    res.writeHead(200, {"Content-Type": "text/html"});
    
    let html = "";
    for (let key in query){
        html += "<h1>"+key + ": "+query[key] +"</h1>";
    }
    res.end(html);
    
}).listen(3000, ()=>{
    console.log("Server Running at http://localhost:3000");
});