const express = require('express');

const port = 7166;

const app = express();

app.get('/', (req, res) => {
    res.writeHead(200, {
        'Content-Type': 'text/html; charset=utf-8'
    });
    const message = `
    <h1>This is a node application running on the docker container!</h1>
    <h2>This line is for testing the change of index.js</h2>
    <h3>Build the 'Dockerfile' and chech the docker build process</h3>
    <h3>This line is for docker volume test. Please stop the container and run run-dev.sh WHEN you changed this line!</h3>
    `
    res.end(message);
});

app.listen(port, () => {
    console.log(`The application is running with the port ${port}`);
});