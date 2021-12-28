// 예제를 위한 비동기 함수
const readFileAsync = (filename, cb) => {
  setImmediate(()=> {
    console.log(`readFile : ${filename}`);

    const data = `data of ${filename}`;
    cb(null, data);
  });
}

// 예측할 수 없는 함수 : 동기와 비동기 조합
const cache = new Map();
const inconsistentRead = (filename, cb) => {
  // 캐시에 있으면 동기 작업
  if(cache.has(filename)) {
    cb(cache.get(filename));
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
  inconsistentRead(filename, value => {
    // 비동기 작업의 경우, onDataReady에 리스너 등록 가능
    // 동기 작업의 경우, onDataReady를 통해 리스너 등록 전에 아래 코드가 실행됨
    console.log('listenrs :', listeners);
    listeners.forEach(listener => listener(value));
  });

  return {
    onDataReady: listener => listeners.push(listener)
  }
}

// 첫번째 리더 : data.txt 파일을 비동기적으로 읽음
// => 리스너들 호출 전에 onDataReady에 리스너 등록 시간이 충분
const reader1 = createFileReader('data.txt');
reader1.onDataReady((data) => {
  console.log(`First call data : ${data}`);

  // 두번째 리더 : 같은 파일을 읽으므로 동기 방식
  // => 리스너들이 바로 호출되어 onDataReady에 리스너 등록 불가능
  const reader2 = createFileReader('data.txt');
  reader2.onDataReady((data) => {
    console.log(`Second call data : ${data}`);
  })
})