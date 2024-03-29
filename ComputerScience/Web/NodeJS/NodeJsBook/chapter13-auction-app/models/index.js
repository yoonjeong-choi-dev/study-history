const Sequelize = require('sequelize');

// DB 관련 설정 로드
const env = process.env.NODE_ENV || 'development';
const config = require('../config/config')[env];

const User = require('./user');
const Good = require('./good');
const Auction = require('./auction');

// config.json의 내용을 통해 해당 DB와의 연결 객체 생성
const db = {};
const sequelize = new Sequelize(
  config.database, config.username, config.password, config,
);

// 외부에서 사용할 db 모듈 설정
db.sequelize = sequelize;
db.User = User;
db.Good = Good;
db.Auction = Auction;

// 시퀄라이즈 연결 객체를 모델로 주입
User.init(sequelize);
Good.init(sequelize);
Auction.init(sequelize);

// db 객체를 모델로 주입 : 모델 관계 정의
User.associate(db);
Good.associate(db);
Auction.associate(db);

module.exports = db;