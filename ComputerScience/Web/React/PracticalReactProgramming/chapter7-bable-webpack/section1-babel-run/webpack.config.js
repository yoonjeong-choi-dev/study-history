const path = require('path');

module.exports = {
  entry: './src/simple-code.js',
  output: {
    path: path.resolve(__dirname, 'dist'),
    filename: 'simple-code.js',
  },
  module: {
    rules: [{ test: /\.js$/, use: 'babel-loader' }],  // babel.config.js 설정 사용
  },
  optimization: { minimizer: [] },  // 결과값 출력을 위해 압축 기능 off
};
