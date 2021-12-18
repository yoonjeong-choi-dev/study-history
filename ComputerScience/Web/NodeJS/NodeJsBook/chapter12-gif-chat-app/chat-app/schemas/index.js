const mongoose = require('mongoose');

const { MONGO_ID, MONGO_PASSWORD, NODE_ENV } = process.env;

// db 연결 함수
const connect = () => {
    if (NODE_ENV !== 'production') {
        mongoose.set('debug', true);
    }

    // 로컬 db 연결에 필요한 정보들
    const host = 'localhost:27017';
    const dbName = 'nodejs_gif_chat';
    const url = `mongodb://${MONGO_ID}:${MONGO_PASSWORD}@${host}/?authSource=${dbName}&readPreference=primary&appname=MongoDB%20Compass&ssl=false`
    mongoose.connect(url, {
        dbName: dbName,
        autoCreate: true,
        autoIndex: true,
    }, (err) => {
        if (err) {
            console.error(`Fail to connect : ${err}`);
        } else {
            console.log('Success to connect');
        }
    });
}

mongoose.connection.on('error', (err) => {
    console.error(`Fail to connect : ${err}`);
});
mongoose.connection.on('disconnected', () => {
    console.error('Disconnected. Try to connect again');
    connect();
});

module.exports = connect;