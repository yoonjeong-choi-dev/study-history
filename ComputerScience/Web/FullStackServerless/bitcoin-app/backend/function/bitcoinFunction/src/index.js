const awsServerlessExpress = require('aws-serverless-express');
const app = require('./app');

// app.js를 이용하는 서버 인스턴스 생성
const server = awsServerlessExpress.createServer(app);

// 함수 호출의 시작 지점
exports.handler = (event, context) => {
  console.log(`EVENT: ${JSON.stringify(event)}`);

  // app.js에서 실행 중인 express 서버로 이벤트 및 컨텍스트 전달
  // => express 서버에서 path를 통한 라우팅 가능
  return awsServerlessExpress.proxy(server, event, context, 'PROMISE').promise;
};
