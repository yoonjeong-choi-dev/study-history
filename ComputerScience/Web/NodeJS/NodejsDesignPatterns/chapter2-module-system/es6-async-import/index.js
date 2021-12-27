// 지원하는 언어 및 사용자 입력
const SUPPORTED_LANGUAGES = ['en', 'es', 'it','kr'];
const selected = process.argv[2];

if (!SUPPORTED_LANGUAGES.includes(selected)) {
  console.error('The specified language is not supported');
  process.exit(1);
}

// 런타임에서 비동기적으로 모듈 임포트
const selectedModule = `./strings-${selected}.js`;
import(selectedModule)
  .then((ret) => {
    console.log('result of import', ret);
    console.log(ret.HELLO);
  })