// 외부에서 만든 모듈 임포트
const someModule = (() => {
  // 비공개할 private 메서드 및 변수
  const privateFunc = () => {};
  const privateVar = [];

  // 공개할 메서드 및 변수
  const exported = {
    publicFunc : () => {},
    publicVar : [],
  };

  // 공개할 메서드 및 변수 반환
  return exported;
})(); // 함수를 바로 실행하여 모듈 임포트


// 모듈이 공개한 내용 
console.log('Public',someModule);
console.log('Private', someModule.privateFunc, someModule.privateVar);
