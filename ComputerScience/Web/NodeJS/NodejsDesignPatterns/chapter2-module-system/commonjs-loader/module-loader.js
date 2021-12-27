// 파일시스템 모듈 자체는 CommonJS로 임포트
const fs = require('fs');


const loadModule = (filename, module, require) => {
  // 모듈이 있는 동기로 파일을 읽음 like CommonJS
  // 여기서 만든 모듈 관련 컨텍스트(module, module.exports, require)를 임포트할 모듈로 전달
  const wrappedSrc = 
  `(function (module, exports, require) {
    ${fs.readFileSync(filename, 'utf8')}  // filename 스크립트에서는 yjRequire 관련 컨텍스트 사용
  })(module, module.exports, require)`; // revealing-module-pattern

  // 해당 소스 실행
  eval(wrappedSrc);
};

// CommonJS의 require 동작을 모방하여 구현
var yjRequire = (moduleName) => {
  console.log(`yjRequire invoked for module: ${moduleName}`);
  
  // 임포트할 모듈의 경로 찾아 이미 로드된 경우 그대로 반환
  const id = yjRequire.resolve(moduleName);
  if(yjRequire.cache[id]) {
    return yjRequire.cache[id].exports;
  }

  // 로드할 모듈의 메타데이터 : 
  // loadModule로 불러온 모듈의 코드에서 익스포트한 public API를 저장하는 용도
  const module = {
    exports: {},
    id,
  };

  // 캐시 업데이트
  yjRequire.cache[id] = module;

  // 모듈 로드 : 파일 이름, export한 API 저장할 module 객체, 모듈 임포트 함수인 yjRequire
  loadModule(id, module, yjRequire);

  console.log(module);

  // 익스포트된 API 반환
  return module.exports;
}

// 모듈 경로의 캐싱을 위한 변수 i.e 메모리에 로드되어 있는지 여부 확인
yjRequire.cache = {};

// 모듈의 전체 경로를 알아내는 메서드
yjRequire.resolve = (moduleName) => {
  // 이 부분은 간소화를 위해 기존 require.resolve 사용
  return require.resolve(moduleName);
}

// usage : node module-loader.js <진입 파일>
// 이후 다른 파일에서는 yjRequire 사용 가능
yjRequire(process.argv[2]);