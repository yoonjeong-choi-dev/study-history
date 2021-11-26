const crypto = require('crypto');

const pw = "yoonjeong-choi-password";
console.log('Origin password : ', pw);


console.log('\n-------------------------------------------------');
console.log('hash example 1 : sha512');
console.log('-------------------------------------------------');

console.log('Hashed : ', crypto.createHash('sha512'));
console.log('base64 : ', crypto.createHash('sha512').digest('base64'));
console.log('hex : ', crypto.createHash('sha512').digest('hex'));


console.log('\n-------------------------------------------------');
console.log('hash example 2 :pbkdf2');
console.log('-------------------------------------------------');

// 내부적으로 멀티스레딩 동작
crypto.randomBytes(64, (err, buf) => {
    // 기존 문자열에 덧붙이는 랜덤 솔트
    const salt = buf.toString('base64');
    console.log('salt : ', salt);

    // repeatNum 만큼 해시 적용
    const repeatNum = 100000;
    crypto.pbkdf2(pw, salt, repeatNum, 64, 'sha512', (err, key) => {
        console.log('hashed pw : ', key.toString('base64'));
    });
})

// 위 예제를 다 돌리고 다음 예제를 돌리기 위해 타임 아웃
setTimeout(() => {
    console.log('\n-------------------------------------------------');
    console.log('cipher example');
    console.log('-------------------------------------------------');

    const myMessage = "Hello My name is Yoonjeong Choi!";
    const algorithm = 'aes-256-cbc';
    const key = 'yoonjeong-choi-private-key123456';   // 32바이트
    const initVector = '1234567890123456';      //16 바이트

    const cipher = crypto.createCipheriv(algorithm, key, initVector);
    let encrypted = cipher.update(myMessage, 'utf8', 'base64');
    encrypted += cipher.final('base64');

    const decipher = crypto.createDecipheriv(algorithm, key, initVector);
    let decrypted = decipher.update(encrypted, 'base64', 'utf8');
    decrypted += decipher.final('utf8');

    console.log('Original Message : ', myMessage);
    console.log('Encrypted Message : ', encrypted);
    console.log('Decrypted Message : ', decrypted);
}, 1000);

