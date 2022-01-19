const babel = require('@babel/core');
const fs = require('fs');

// 컴파일 대상 및 환경 설정
const filename = './src/simple-code.js';
const source = fs.readFileSync(filename, 'utf8');
const presets = ['@babel/preset-react'];
const plugins = [
  '@babel/plugin-transform-template-literals',
  '@babel/plugin-transform-arrow-functions',
];

// 바벨로 컴파일한 결과
const { code } = babel.transformSync(source, {
  filename,
  presets,
  plugins,
  configFile: false,
});
console.log(code);
