function delayPromise(milliseconds) {
  // 새로운 프라미스 반환
  return new Promise((resolve, reject) => {
    // setTimeout 비동기 함수 내에서 resolve 이행
    setTimeout(()=> {
      // resolve는 현재 시간에 대한 Date 객체 반환
      resolve(new Date());
    }, milliseconds)
  });
}

console.log(`Before delaying... ${new Date().getSeconds()}s`);
delayPromise(1000)
  .then(date => console.log(`After delaying... ${date.getSeconds()}s`));