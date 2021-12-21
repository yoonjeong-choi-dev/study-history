const express = require('express');
const app = express();

app.use((req, res, next) => {
    console.log('--------------------------------------');
    console.log('First middleware : Always');
    next();
});

app.get('/a', (req, res) => {
    console.log('/a : route terminated');
    res.send('a');
});

app.get('/b', (req, res, next) => {
    console.log('/b : route not terminated');
    next();
});

app.use((req, res, next) => {
    console.log('Middle ware for /b and /c and /');
    next();
});

app.get('/b', (req, res, next) => {
    console.log('/b (2) : error throw');
    throw new Error('get /b : failed');
});

// error handling for /b => server error
app.use('/b', (err, req, res, next) => {
    console.log('Middleware : /b error detected and passed on');
    next(err);
});

app.get('/c', (err, req) => {
    console.log('/c : error throw');
    throw new Error('get /c : failed');
});

// error handling for /c => client error
app.use('/c', (err, req, res, next) => {
    console.log('Middleware : /c error deteced but not passed on');
    next();
});

// fallback handler
app.use((err, req, res, next) => {
    console.log('unhandled error detected : ', err.message);
    res.send('500 - server error');
});

// 404
app.use((req, res) => {
    console.log('route not handled');
    res.send('404 - not found');
});

const port = 7166;
app.listen(port, () => {
    console.log(`express server stated on localhost:${port}`);
});