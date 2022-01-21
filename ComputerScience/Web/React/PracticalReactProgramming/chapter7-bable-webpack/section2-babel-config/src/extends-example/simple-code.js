// preset-react를 이용하여 jsx 변환
const element = <div>babel test</div>;

// plugin-transform-template-literals를 이용하여 템플릿 리터럴 변환
const text = `element type is ${element.type}`;

// plugin-transform-arrow-functions를 이용하여 화살표 함수 변환
const add = (a, b) => a + b;