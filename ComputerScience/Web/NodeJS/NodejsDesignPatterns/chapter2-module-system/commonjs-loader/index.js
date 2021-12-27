const moduleA = yjRequire('./moduleA');

console.log('This is the entry point');
console.log('=========== require context===========');
console.log('require', yjRequire);
console.log('module', module);
console.log('exports', exports);
console.log('======================================');
moduleA.run();