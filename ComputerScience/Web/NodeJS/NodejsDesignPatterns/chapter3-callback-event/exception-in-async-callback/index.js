// 예제를 위한 비동기 함수
const passDataAsync = (data, cb) => {
  setImmediate(()=> {
    cb(null, data);
  });
}

const readJSON = (jsonStr, cb) => {
  passDataAsync(jsonStr, (err, data) => {
    if (err) {
      return cb(err);
    }

    // JSON.parse 예외 발생
    // 해당 예외는 passDataAsync의 콜백 스택에서 발생
    // i.e 이벤트 루프에서 호출 스택 예외가 발생
    cb(null, JSON.parse(data));
  });
}

const wrongJSON = '{hello:"world"}';
try {
  readJSON(wrongJSON, (err) => console.error(err));
} catch(err) {
  // 애플리케이션의 호출 스택에서 발생한 예외를 잡는 부분
  // 이벤트 루프의 호출 스택에서 발생한 예외는 파악 불가능
  console.error('This will NEVER catch the JSON.parse exception');
}

// 위와 같은 상황에서 잡을 수 없는 예외 발생 시, node에서 uncaughtException 이벤트 발생
process.on('uncaughtException', (err) => {
  // 필요한 작업 정리
  console.error(`The process will be terminated because.. ${err.message}`);

  // fail-fast : 즉시 종료 후, 다시 재실행 필요
  process.exit(1);
})