import { fileURLToPath } from 'url';
import { dirname } from 'path';
import { createRequire } from 'module';

// 툭수 변수들을 ES6 에서 사용하기
const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);

console.log('__filename :', __filename);
console.log('__dirname :', __dirname);

// commonjs 모듈 및 json 임포트를 위한 require 함수 선언
const require = createRequire(import.meta.url);

// json 임포트
const data = require('./data.json');
console.log('json data :', data);

const cjs = require('./cjs-module.cjs');
cjs();