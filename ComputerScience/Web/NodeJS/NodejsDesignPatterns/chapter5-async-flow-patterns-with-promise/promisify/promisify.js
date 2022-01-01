// 인자로 받은 콜백 기반 함수를 이용하여 프라미스를 반환하는 함수
module.exports = function promisify(callbackBasedApi) {
  // promisified 반환값 : 입력으로 주어진 콜백 기반 함수의 프라미스 버전
  // callbackBasedApi(...args)에 대한 프라미스 버전
  return function promisified(...args) {
    
    return new Promise((resolve, reject) => {
      const newArgs = [
        ...args,
        // 콜백 규약 : 함수의 마지막 인자로 (err, result)=>{} 형식
        // => 콜백 기반 함수의 마지막 인자로 넘겨주기 위해 콜백 추가
        function (err, result) {
          if (err) {
            reject(err);
          }

          resolve(result);
        }
      ];

      // 콜백 기반 함수에 인자들과 콜백 함수를 넘겨줘서 실행
      callbackBasedApi(...newArgs);
    });
  }
}