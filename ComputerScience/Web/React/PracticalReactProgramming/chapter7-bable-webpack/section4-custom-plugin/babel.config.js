// 커스텀 플러그인 등록
//const plugins = ['./plugins/remove-log.js'];
const plugins = ['./plugins/insert-log.js'];

// 아래 방식으로하면 on함수의 로그도 사라짐
//const plugins = ['./plugins/remove-log.js', './plugins/insert-log.js']

module.exports = { plugins };