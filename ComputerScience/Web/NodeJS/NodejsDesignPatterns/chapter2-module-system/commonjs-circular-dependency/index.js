// a,b 임포트 순서에 따라 결과가 다르게 나옴
const b = require('./b');
const a = require('./a');
//const b = require('./b');

console.log('a->', JSON.stringify(a, null, 2));
console.log('b->', JSON.stringify(b, null, 2));