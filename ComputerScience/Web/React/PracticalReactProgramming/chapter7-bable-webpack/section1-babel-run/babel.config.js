// run-babel-cli에서 설정했던 옵션들
const presets = ['@babel/preset-react'];
const plugins = [
  '@babel/plugin-transform-template-literals',
  '@babel/plugin-transform-arrow-functions',
];

module.exports = { presets, plugins };
