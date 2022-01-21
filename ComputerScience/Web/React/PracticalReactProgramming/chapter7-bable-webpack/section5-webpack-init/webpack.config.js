const path = require('path');

module.exports = {
  entry: './src/index.js',  // 진입점 코드
  output: {
    filename: 'yjBundle.js',  // 번들 파일 이름
    path: path.resolve(__dirname, 'dist'),
  },
  mode: 'production',       // 운영 환경
  optimization: {minimizer: []},  // 코드 압축
}