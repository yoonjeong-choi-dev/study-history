const express = require('express');
const redis = require('redis');

const port = 7166;

const app = express();

// 레디스 클라이언트 생성
const redisClient = redis.createClient({
    host: 'redis-server',    // 도커 컴포즈에서 정의한 레디스 서버 컨테이너의 호스트
    port: 6379,             // 레디스 서버 기본 포트
});


// 레디스 서버에 데이터 초기화
redisClient.set('number', 1);

app.get('/', (req, res) => {
    // 현재 접속 횟수 
    redisClient.get('number',(err, curCount) => {
        res.set('Content-Type', 'text/html; charset=utf-8')

        const message = `
        <h1>This is a node application running on the docker container!</h1>
        <h3> The number of visit : ${curCount} </h3>
        `;
        res.send(message);
    
        // 클라이언트에서 접속할 때마다 값 증가
        redisClient.set('number', parseInt(curCount) + 1);
    });
});

app.listen(port, () => {
    console.log(`The application is running with the port ${port}`);
});