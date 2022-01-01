const promisify = require('./promisify');
const { randomBytes } = require('crypto');

const randomBytesPromisified = promisify(randomBytes);
randomBytesPromisified(32)
  .then(buffer => {
    console.log(`Random Bytes : ${buffer.toString()}`);
  });