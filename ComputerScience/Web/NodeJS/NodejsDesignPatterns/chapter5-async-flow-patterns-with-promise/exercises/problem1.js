async function myPromiseAll(promises) {
  // 각 프라미스에 대해서 실행
  // 에러처리는 caller에서 처리해야 하기 때문에 예외 처리 x
  for (let promise of promises)
    await promise;
}


// 예제를 위한 프라미스 생성 함수
function delayResolve(milliseconds) {
  // 새로운 프라미스 반환
  return new Promise((resolve, reject) => {
    // setTimeout 비동기 함수 내에서 resolve 이행
    setTimeout(() => {
      // resolve는 현재 시간에 대한 Date 객체 반환
      console.log(`delayRosolve(${milliseconds}) is called`);
      resolve(new Date());
    }, milliseconds)
  });
}

function delayError(milliseconds) {
  return new Promise((resolve, reject) => {
    // setTimeout 비동기 함수 내에서 resolve 이행
    setTimeout(() => {
      // resolve는 현재 시간에 대한 Date 객체 반환
      console.log(`delayError(${milliseconds}) is called`);
      reject(new Error(`Error atfer ${milliseconds}s`));
    }, milliseconds)
  });
}

const delimeterLogging = () => {
  console.log('----------------------------');
}

// Promise.all([
//   delayResolve(1000),
//   delayResolve(1500),
//   delayResolve(1200),
//   delayResolve(1100),
//   delayError(2000),
//   delayError(1300),
//   delayError(2500),
// ]).then(() => {
//     delimeterLogging();
//     console.log('All promises are resovled');
//     delimeterLogging();
//   })
//   .catch(err => {
//     delimeterLogging();
//     console.log('Some promise is rejected');
//     console.log(`Error : ${err.message}`);
//     delimeterLogging();
//   });



myPromiseAll([
  delayResolve(1000),
  delayResolve(1500),
  delayResolve(1200),
  delayResolve(1100),
  delayError(2000),
  delayError(1300),
  delayError(2500),
]).then(() => {
    delimeterLogging();
    console.log('All promises are resovled');
    delimeterLogging();
  })
  .catch(err => {
    delimeterLogging();
    console.log('Some promise is rejected');
    console.log(`Error : ${err.message}`);
    delimeterLogging();
  });