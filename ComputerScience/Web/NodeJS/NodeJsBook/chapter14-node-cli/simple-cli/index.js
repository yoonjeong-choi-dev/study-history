#!/usr/bin/env node
const readline = require('readline');

// 표준 입출력을 이용하여 인터페이스 정의
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
});

const answerCallback = (answer) => {
    if ( answer === 'y') {
        console.log('You are YJ');
        rl.close();
    } else if (answer === 'n') {
        console.log('You are not YJ');
        rl.close();
    } else {
        console.clear();
        console.log('Please enter only y/n');
        rl.question('Are you YJ? (y/n) : ', answerCallback);
    }
};

rl.question('Are you YJ? (y/n) : ', answerCallback);