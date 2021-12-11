const express = require('express');
const expressHandlebars = require('express-handlebars');

const app = express();
const port = process.env.PORT || 3000;

// 뷰 엔진 설정
app.engine('handlebars', expressHandlebars({
    defaultLayout: 'defaultLayout'   // 기본 레이아웃 설정
}));
app.set('view engine', 'handlebars');

// 정적 리소스 미들웨어 설정
app.use(express.static(__dirname + '/public'));

// routing with url
app.get('/', (req, res) => {
    res.render('index');
})


const fortunes = [
    "Conquer your fears or they will conquer you.",
    "Rivers need springs.",
    "Do not fear what you don't know.",
    "You will have a pleasant surprise.",
    "Whenever possible, keep it simple.",
]

app.get('/about', (req, res) => {
    const randomFortune = fortunes[Math.floor(Math.random() * fortunes.length)];
    res.render('about', {
        fortune: randomFortune
    });
})

// Custom 404 page
app.use((req, res) => {
    res.status(404);
    res.render('clientError');
});

// Custom 500 page
app.use((err, req, res, next) => {
    console.log(err.message);

    res.status(500);
    res.render('serverError');
});

// Open the port
app.listen(port, () => {
    console.log(`Express Server started on http://localhost:${port}`);
})