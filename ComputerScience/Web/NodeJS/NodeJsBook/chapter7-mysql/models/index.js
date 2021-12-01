const Sequelize = require('sequelize');

// 정의한 모델 임포트
const User = require('./user');
const Comment = require('./comment');

const env = process.env.NODE_ENV || 'development';
const config = require(__dirname + '/../config/config.json')[env];


// config.json의 내용을 통해 해당 DB와의 연결 객체 생성
const sequelize = new Sequelize(config.database, config.username, config.password, config);

// 외부에서 사용할 db 모듈 설정
const db = {};
db.sequelize = sequelize;
db.User = User;
db.Comment = Comment;

// 시퀄라이즈 연결 객체를 모델로 주입
User.init(sequelize);
Comment.init(sequelize);

// db 객체를 모델로 주입
User.associate(db);
Comment.associate(db);

module.exports = db;
