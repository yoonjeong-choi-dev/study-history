import { count, increment } from './counter.js';

console.log(count);

increment();
console.log('after call increment :', count);

console.log('Try : count=4');
count = 4;  // 임포트한 변수들은 모두 읽기 전용