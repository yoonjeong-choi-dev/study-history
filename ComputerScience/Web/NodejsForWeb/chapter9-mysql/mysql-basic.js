var mysql = require("mysql");

var client = mysql.createConnection({
    user: "root",
    password: "1234"
});

client.query("USE Company");
client.query("SELECT * FROM products", (err, result, fields)=>{
    if(err){
        console.log("Wrong Query");
    }
    else{
        console.log(result);
    }
})