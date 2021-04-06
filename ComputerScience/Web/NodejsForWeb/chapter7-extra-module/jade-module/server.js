var http = require("http");
var fs = require("fs");
var jade = require("jade");

http.createServer((req, res)=>{
    fs.readFile(__dirname+"/index.jade", "utf8", (err, data)=>{
        res.writeHead(200, {"Content-Type": "text/html"});
        
        var jadeFunc = jade.compile(data)

        htmlText= jadeFunc({
            name: "Yoonjeong Choi",
            description: "I am an engineer"
        });
        res.end(htmlText);
    })
    

    
}).listen(3000, ()=>{
    console.log("Server Running at http://localhost:3000");
});