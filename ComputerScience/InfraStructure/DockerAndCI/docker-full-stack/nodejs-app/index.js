const express = require('express');
const db = require('./db');

const port = 5123;

const app = express();

// 미들웨어 설정
app.use(express.json());

// 테이블 생성
db.pool.query(`CREATE TABLE lists (
    id INTEGER AUTO_INCREMENT,
    value TEXT, 
    PRIMARY KEY (id)
)`, (err, results, fileds) => {
    console.log('results', results)
});

// API 구현
app.get('/api/values', (req, res) => {
    // DB에 있는 모든 정보 가져오기
    db.pool.query(`SELECT * FROM lists;`, (err, result, fields) => {
        // 쿼리 도중 에러 발생 시 500 에러 반환
        if (err)
            return res.status(500).send(err);

        // 쿼리 결과 반환
        return res.json(result);
    })
});

app.post('/api/value', (req, res, next) => {
    // 요청 바디의 정보를 DB에 저장
    const {value} = req.body;

    db.pool.query(`INSERT INTO lists (value) VALUES("${value}")`,(err, result, fields) => {
        // 쿼리 도중 에러 발생 시 500 에러 반환
        if (err)
            return res.status(500).send(err);

        // 저장 성공 메시지 반환
        return res.json({
            success: true,
            value: value,
        });
    })
})

// 서버 실행
app.listen(port, () => {
    console.log(`Server started on the port ${port}`);
});