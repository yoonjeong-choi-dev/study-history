function delay(milliseconds) {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      resolve(new Date());
    }, milliseconds);
  })
}

// 주어신 시간이 지난 후, 현재 시간 출력을 반복하기 위한 재귀 함수
function leakingLoop() {

  // 프라미스 체인이 무한 개로 늘어나고, 메모리 누수 발생
  return delay(1)
    .then(() => {
      console.log(`Tick ${Date.now()}`);
      return leakingLoop();
    });
}

// 해결책 1 : 프라미스 해결(resolve) 체인을 끊는 것
// return을 없앰으로써, 프라미스 체인을 연결하지 않음
function nonLeakingLoop() {
  delay(1)
    .then(() => {
      console.log(`Tick ${Date.now()}`);
      nonLeakingLoop();
    });
}

// 해결책 2 : 재귀 함수를 프라미스 생성자로 래핑
// => 프라미스 해결 체인을 끊는 것과 동시에 에러 전파 가능
function nonLeakingLoopWithWrapper() {
  return new Promise((resolve, reject) => {
    (function recursive() {
      delay(1)
        .then(() => {
          console.log(`Tick ${Date.now()}`);
          recursive();
        })
        .catch(err => {
          reject(err);
        });
    })
  })
}

// 해결책 3 : async/await을 이용한 무한 루프
async function nonLeakingLoopWithInfiniteAwait() {
  while (true) {
    await delay(1);
    console.log(`Tick ${Date.now()}`);
  }
}

// 잘못된 해결책 : async/await을 이용한 재귀 함수
// 재귀함수는 함수 스택에 계속 쌓여서 메모리 누수 발생
async function nonLeakingLoopWithRecursiveAwait() {

  await delay(1);
  console.log(`Tick ${Date.now()}`);
  nonLeakingLoopWithRecursiveAwait();
}


function memoryLeakTest(loop) {
  for (let i = 0; i < 1e6; i++)
    loop();
}

//memoryLeakTest(leakingLoop);
//memoryLeakTest(nonLeakingLoop);
//memoryLeakTest(nonLeakingLoopWithWrapper)
//memoryLeakTest(nonLeakingLoopWithInfiniteAwait)
memoryLeakTest(nonLeakingLoopWithRecursiveAwait)