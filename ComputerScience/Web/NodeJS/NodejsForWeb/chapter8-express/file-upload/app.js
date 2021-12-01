var express = require("express");
var fs = require("fs");
var multipart = require("connect-multiparty");

var app = express();

const FOLDER_NAME = "/myfolder"

// Set middlewares
app.use(multipart({ uploadDir: __dirname + FOLDER_NAME }));


app.get("/", (req, res) => {

    fs.readFile(__dirname + "/index.html", (err, data) => {
        if (err) {
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


// 파일 업로드
app.post("/", (req, res) => {
    var comment = req.body.comment;
    var fileInfo = req.files.uploadfile;

    var filename = fileInfo.name;
    var filepath = fileInfo.path;
    var fileType = fileInfo.type;
    console.log(fileType)
    if (fileInfo.size>0) {
        

        // exe 파일은 업로드 금지 : 삭제
        if (fileType.indexOf("application") != -1) {
            console.warn("exe file uploaded!")
            fs.unlink(filepath, (error) => {
                res.sendStatus(400);
            })
        }
        else {
            // 파일 이름 변경
            if (comment == "" || comment == "undefined" || comment==null){
                comment = "fileUploaded";
            }

            var outputPath = __dirname + FOLDER_NAME +"/"+ comment+ "-"+ filename;
            fs.rename(filepath, outputPath, (err)=>{
                res.redirect("/");    
            })
            
        }
    }
    else {
        console.log("Empty File");
        fs.unlink(filepath, (error) => {
            res.redirect("/");  
        })
        
    }

    
})



app.listen(3000, () => {
    console.log("Server Running at http://localhost:3000");
})