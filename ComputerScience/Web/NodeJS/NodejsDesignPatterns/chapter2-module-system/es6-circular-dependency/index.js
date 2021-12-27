import * as a from './a.js';
import * as b from './b.js';

// a.b는 b를 참조하고 있는 형식
// b.a는 a를 참조하고 있는 형식
// => JSON.stringify()는 사용 불가
console.log('index.js : main process run...');
console.log('a->', a);
console.log('b->', b);