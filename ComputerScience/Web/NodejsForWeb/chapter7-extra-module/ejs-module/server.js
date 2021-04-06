var http = require("http");
var fs = require("fs");
var ejs = require("ejs");

http.createServer((req, res)=>{
    fs.readFile(__dirname+"/index.ejs", "utf8", (err, data)=>{
        res.writeHead(200, {"Content-Type": "text/html"});
        res.end(ejs.render(data,{
            name: "Yoonjeong Choi",
            description: "Hello ejs with Node.js"
        }));
    })
    

    
}).listen(3000, ()=>{
    console.log("Server Running at http://localhost:3000");
});