const mongoose = require('mongoose');

// db 연결 함수
const connect = () => {
    if (process.env.NODE_ENV !== 'production') {
        mongoose.set('debug', true);
    }

    // 로컬 db 연결에 필요한 정보들
    const id = 'nodejsuser';
    const pwd = 'nodejsuser';
    const host = 'localhost:27017';
    const dbName = 'nodejs_test';
    const url = `mongodb://${id}:${pwd}@${host}/?authSource=${dbName}&readPreference=primary&appname=MongoDB%20Compass&ssl=false`
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