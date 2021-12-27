const moduleB = yjRequire('./moduleB');

module.exports = {
  run: () => {
    console.log('From module A : Import module B');
    moduleB.simpleLog();
  },
};