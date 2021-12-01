const { odd, even } = require("./numbers");

const checkOddOrEven = (num) => {
    if (num % 2) {
        return odd;
    } else {
        return even;
    }
};

module.exports = checkOddOrEven;