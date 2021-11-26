const { Worker, isMainThread, workerData, parentPort } = require('worker_threads');

// 부모(메인) 스레드 일 때,
if (isMainThread) {
    // 스레드 생성
    const threads = new Set();
    threads.add(new Worker(__filename, {
        workerData: { start: 1 },
    }));
    threads.add(new Worker(__filename, {
        workerData: { start: 2 },
    }));

    // 각 스레드(워커)에 이벤트 리스너 등록 : 부모 스레드로부터 데이터 받음
    for (let worker of threads) {
        worker.on('message', message => console.log('from worker : ', message));
        worker.on('exit', () => {
            // 스레드풀에서 해당 워커 삭제
            threads.delete(worker);

            // 모든 워커 삭제 시
            if (threads.size === 0) {
                console.log('job done');
            }
        });
    }
} else {
    // 워커 스레드일 때 : 스레드 생성 시 부모에게서 전달 받은 데이터를 다시 부모에게 전달
    const data = workerData;
    parentPort.postMessage(data.start + 100);
}