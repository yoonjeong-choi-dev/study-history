const { Worker, isMainThread, workerData, parentPort } = require('worker_threads');

let primes = [];

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



// 부모(메인) 스레드 일 때,
if (isMainThread) {
    const max = 10000000;
    const min = 2;
    const threadCount = 10;

    // 각 스레드에서 처리할 숫자 갯수
    const range = Math.ceil((max-min)/threadCount);

    // 스레드 생성
    const threads = new Set();
    let start = min;
    console.time('prime');  // 소수 찾기 메인 프로세스 시작
    for (let i=0;i<threadCount-1;i++){
        const workerStart = start;

        // 각 스레드에서 처리할 숫자 범위 데이터를 넘겨준다
        threads.add(new Worker(__filename, {
            workerData: { start: workerStart, range}
        }));

        start += range;
    }
    // 마지막 스레드는 나머지 숫자 처리
    threads.add(new Worker(__filename, { 
        workerData: { 
            start, 
            range: range + ((max - min + 1) % threadCount) 
        } }));

    // 각 스레드(워커)에 이벤트 리스너 등록 : 부모 스레드로부터 데이터 받음
    for (let worker of threads) {
        worker.on('error', err => {throw err;});
        worker.on('exit', () => {
            // 스레드풀에서 해당 워커 삭제
            threads.delete(worker);

            // 모든 워커 삭제 시
            if (threads.size === 0) {
                console.timeEnd('prime');
                console.log(primes.length);
            }
        });

        // 각 스레드가 만든 소수 숫자 리스트를 업데이트
        worker.on('message', message => {
            primes = primes.concat(message);
        });
    }

    
} else {
    // 워커 스레드일 때 : 소수 찾기
    findPrimes(workerData.start, workerData.range);
    parentPort.postMessage(primes);
}