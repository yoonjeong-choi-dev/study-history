const mysql = require('mysql');

// TODO : 데이터베이스 연결 관련 정보들은 환경 변수로 대체 필요
// 개발용과 같이 쓰기 위해 운영용 환경변수 가없는 경우 개발 용 변수 할당
exports.pool = mysql.createPool({
    connectionLimit: 10,
    host: process.env.MYSQL_HOST || 'mysql',  // 도커 컴포즈에서 정의한 db 서비스 이름
    user: process.env.MYSQL_USER || 'root',
    password: process.env.MYSQL_ROOT_PASSWORD || 'yjdbpassword',
    database: process.env.MYSQL_DATABASE || 'yjApp',
    port: process.env.MYSQL_PORT || 3306,
});
