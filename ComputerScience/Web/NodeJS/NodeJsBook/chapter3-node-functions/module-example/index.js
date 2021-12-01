const { odd, even } = require("./numbers");
const checkNumber = require("./myfunctions");

const checkStringLengthOddOrEven = (str) => {
    const ret = `The length of the "${str}"`;
    if (str.length % 2){
        return `${ret} : ${odd}`;
    } else {
        return `${ret} : ${even}`;
    }
};

console.log(checkNumber(15));
console.log(checkStringLengthOddOrEven("Hello!"));