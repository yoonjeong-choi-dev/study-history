const mongoose = require('mongoose');

const { Schema } = mongoose;
const { Types : {ObjectId} } = Schema;

const chatSchema = new Schema({
    room: {
        type: ObjectId,
        required: true,
        ref: 'Room',    // Room 콜렌션과 연결
    },
    user: {
        type: String,
        required: true,
    },
    // 채팅 메시지나 GIF 파일 중 하나만 있으면 작성 가능
    chat: String,
    gif: String,
    createdAt: {
        type: Date,
        default: Date.now
    },
});

module.exports = mongoose.model('Chat', chatSchema);