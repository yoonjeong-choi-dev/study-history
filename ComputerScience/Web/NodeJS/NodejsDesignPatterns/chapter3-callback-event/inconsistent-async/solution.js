// 예제를 위한 비동기 함수
const readFileAsync = (filename, cb) => {
  setImmediate(()=> {
    console.log(`readFile : ${filename}`);

    const data = `data of ${filename}`;
    cb(null, data);
  });
}

// 예측할 수 없는 함수 : 동기와 비동기 조합
// => 해결방법 : 완전한 비동기 함수로 변경
const cache = new Map();
const consistentReadAsync = (filename, cb) => {
  if(cache.has(filename)) {
    // 동기 작업을 비동기화
    // nextTick : 현재 진행 중인 작업이 끝나고 제어가 이벤트 루프로 갔을 때 실행
    process.nextTick(() => cb(cache.get(filename)));
  } else {
    // 캐시에 없으면 비동기 작업
    readFileAsync(filename, (err, data) => {
      cache.set(filename, data);
      cb(data);
    })
  }
}

// 파일 읽기 작업에 대한 다수의 리스너 설정 함수
const createFileReader = (filename) => {
  const listeners = [];
  consistentReadAsync(filename, value => {
    // 비동기 작업의 경우, onDataReady에 리스너 등록 가능
    console.log('listenrs :', listeners);
    listeners.forEach(listener => listener(value));
  });

  return {
    onDataReady: listener => listeners.push(listener)
  }
}

const reader1 = createFileReader('data.txt');
reader1.onDataReady((data) => {
  console.log(`First call data : ${data}`);
  const reader2 = createFileReader('data.txt');
  reader2.onDataReady((data) => {
    console.log(`Second call data : ${data}`);
  })
})