var fs = require("fs");
var ejs = require("ejs");
var mysql = require("mysql");
var express = require("express");

// Connect Company DB
var client = mysql.createConnection({
    user: "root",
    password: "1234",
    database: "Company"
});


// Server
var app = express();
app.use(express.urlencoded({ extended: false }));

app.listen(3000, () => {
    console.log("server running at http://localhost:3000");
});


// ERROR UTIL FUNCTION
const errorCheckResponse = (err, res, errorMessage) => {
    if (err) {
        res.writeHead(500, {
            "Content-Type": "text/html"
        });

        html = "<h1>" + errorMessage + "</h1>";
        res.end(html);
    }

}

// Route : main page
app.get("/", (req, res) => {
    fs.readFile(__dirname + "/index.html", "utf8", (err, data) => {
        errorCheckResponse(err, res, "page not found");

        // db query
        client.query("SELECT * FROM products", (err, results) => {
            errorCheckResponse(err, res, "SELECT QUERY ERROR");
            res.send(ejs.render(data, {
                data: results
            }))
        })
    })
})

// Route : delete data
app.get("/delete/:id", (req, res) => {
    // db query
    client.query("DELETE FROM products WHERE id=?", [req.params.id], (err, results) => {
        errorCheckResponse(err, res, "DELETE QUERY ERROR");

        // redirect to main page
        res.redirect("/");
    })
})

// Route : insert page
app.get("/insert", (req, res) => {
    fs.readFile(__dirname + "/insert.html", "utf8", (err, data) => {
        errorCheckResponse(err, res, "page not found");
        res.send(data);
    })
})

// Route : insert data
app.post("/insert", (req, res) => {
    var body = req.body;

    // input validation
    const { name, modelnumber, series } = body;
    if (name == "" || modelnumber == "" || series == "") {
        res.redirect("/");
    }


    // db query
    client.query("INSERT INTO products (name, modelnumber, series) VALUES (?, ?, ?)",
        [name, modelnumber, series], (err, data) => {
            errorCheckResponse(err, res, "INSERT QUERY ERROR");
            res.redirect("/");
        })
})

// Route : edit page
app.get("/edit/:id", (req, res) => {
    fs.readFile(__dirname + "/edit.html", "utf8", (err, data) => {
        errorCheckResponse(err, res, "page not found");

        // db query
        client.query("SELECT * FROM products WHERE id = ?", [req.params.id], (err, results) => {
            errorCheckResponse(err, res, "SELECT QUERY ERROR");
            res.send(ejs.render(data, {
                data: results[0]
            }))
        })
    })
})

// Route : edit data
app.post("/edit/:id", (req, res) => {
    var body = req.body;

    // input validation
    const { name, modelnumber, series } = body;
    if (name == "" || modelnumber == "" || series == "") {
        res.redirect("/");
    }

    // db query
    client.query("UPDATE products SET name=?, modelnumber=?, series=? WHERE id=?",
        [name, modelnumber, series, req.params.id], (err, data) => {
            errorCheckResponse(err, res, "UPDATE QUERY ERROR");
            res.redirect("/");
        })
})