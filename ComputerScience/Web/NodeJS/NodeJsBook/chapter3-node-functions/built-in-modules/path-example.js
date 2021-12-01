const path = require('path');

const curFilePath = __filename;

console.log('path.sep : ', path.sep);
console.log('path.delimiter : ', path.delimiter);

console.log('-----------------------------------');
console.log('current file path : ', curFilePath);
console.log('path.dirname() : ', path.dirname(curFilePath));
console.log('path.extname() : ', path.extname(curFilePath));
console.log('path.basename() : ', path.basename(curFilePath));
console.log('path.basename with file extension : ', path.basename(curFilePath, path.extname(curFilePath)));

console.log('-----------------------------------');
console.log('path.parse() : ', path.parse(curFilePath));

console.log('-----------------------------------');
console.log('path.isAbsolute(/home/yjchoi) : ', path.isAbsolute("/home/yjchoi"));
console.log('path.isAbsolute(../) : ', path.isAbsolute("../"));

console.log('-----------------------------------');
console.log('path.relative() : ', path.relative('/home/yjchoi/apps/Postman', '/home/yjchoi'));
console.log('path.join() : ', path.join(__dirname, '..', '..'));
