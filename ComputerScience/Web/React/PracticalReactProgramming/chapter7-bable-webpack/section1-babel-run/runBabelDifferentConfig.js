const babel = require('@babel/core');
const fs = require('fs');

// 컴파일 대상
const filename = './src/simple-code.js';
const source = fs.readFileSync(filename, 'utf8');

// 컴파일 코드의 AST 분석
const presets = ['@babel/preset-react'];
const {ast} = babel.transformSync(source, {
  filename,
  ast: true,
  code: false,
  presets,
  configFile: false,
});

// 설정 1
const plugins1 = [
  '@babel/plugin-transform-template-literals',
];

// 설정 2
const plugins2 = [
  '@babel/plugin-transform-arrow-functions',
];

// 바벨로 컴파일한 결과
const { code: code1 } = babel.transformFromAstSync(ast, source, {
  filename,
  plugins: plugins1,
  configFile: false,
});

const { code: code2 } = babel.transformFromAstSync(ast, source, {
  filename,
  plugins: plugins2,
  configFile: false,
});

console.log("[Only literal transform]");
console.log(code1);

console.log("\n======================================\n");

console.log("[Only arrow function]");
console.log(code2);
