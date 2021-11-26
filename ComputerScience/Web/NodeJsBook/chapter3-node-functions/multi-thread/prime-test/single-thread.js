const primes = [];

const findPrimes = (start, range) => {
    
    let isPrime = true;
    const end = start + range;

    const min = 2;
    const max = Math.sqrt(end);

    for (let i=start;i<end;i++){
        for (let j=min; j<max;j++) {
            if (i !== j && i%j === 0){
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            primes.push(i);
        }

        isPrime = true;
    }
}

console.time('prime');
findPrimes(2, 10000000);
console.timeEnd('prime');
console.log(primes.length);