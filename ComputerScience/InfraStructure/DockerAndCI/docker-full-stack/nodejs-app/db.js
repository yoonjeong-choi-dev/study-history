const mysql = require('mysql');

// TODO : 데이터베이스 연결 관련 정보들은 환경 변수로 대체 필요
const pool = mysql.createPool({
    connectionLimit: 10,
    host: 'mysql',  // 도커 컴포즈에서 정의한 db 서비스 이름
    user: 'root',
    password: 'yjdbpassword',
    database: 'yjApp',
    port: 3306,
});

exports.pool = pool;