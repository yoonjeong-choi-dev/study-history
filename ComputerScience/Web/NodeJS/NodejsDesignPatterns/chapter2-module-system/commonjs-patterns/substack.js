// 단일 진입점 제공
module.exports = (msg) => {
  console.log(`substack : [info] ${msg}`);
};

// 부가적인 기능 노출 가능
module.exports.warn = (msg) => {
  console.warn(`substack : [warn] ${msg}`);
}