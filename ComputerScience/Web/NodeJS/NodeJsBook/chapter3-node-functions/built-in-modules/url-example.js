const url = require('url');


const urlStr = 'https://www.youtube.com/watch?v=Tdiq7edlvHM&list=RDMM&index=27';
console.log(`My url : ${urlStr}`);

console.log('-----------------------------------');
console.log('WHATWG url format');
const { URL } = url;
const myUrl = new URL(urlStr);
console.log('URL() : ', myUrl);
console.log('url.format() : ', url.format(myUrl));


console.log('-----------------------------------');
console.log('Original node style url format');
const parsedUrl = url.parse(urlStr);
console.log('url.parse() : ', parsedUrl);
console.log('url.format() : ', url.format(parsedUrl));


console.log('-----------------------------------');
console.log('searchParams : ', myUrl.searchParams);
console.log('searchParams.keys() : ', myUrl.searchParams.keys());
console.log('searchParams.values() : ', myUrl.searchParams.values());