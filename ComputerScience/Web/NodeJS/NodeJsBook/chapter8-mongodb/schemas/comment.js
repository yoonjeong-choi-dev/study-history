const mongoose = require('mongoose');

const { Schema } = mongoose;
const { Types: { ObjectId } } = Schema;

// DB document 스키마에 맞게 정의
const commentSchema = new Schema({
  commenter: {
    type: ObjectId,
    required: true,
    ref: 'User',    // 몽구스의 유사 JOIN
  },
  comment: {
    type: String,
    required: true,
  },
  createdAt: {
    type: Date,
    default: Date.now,
  },
});

// 정의한 스키마와 몽고디비 컬렉션 연결
// 첫번째 인자를 이용하여 컬렉션 이름 자동 생성 : Comment -> comments
module.exports = mongoose.model('Comment', commentSchema);