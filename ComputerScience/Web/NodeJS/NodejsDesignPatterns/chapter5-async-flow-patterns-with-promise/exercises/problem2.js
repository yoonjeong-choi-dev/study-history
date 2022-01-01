class TaskQueue {
  constructor(concurrency) {
    // 동시성 제한 개수
    this.concurrency = concurrency || 2;

    // 작업 큐 및 현재 진행 중인 작업의 개수
    this.queue = [];
    this.running = 0;
  }

  runTask(task) {
    return new Promise((resolve, reject) => {
      // 작업에 대한 래퍼 함수를 작업 큐에 넣음
      // 래퍼 함수 호출 시, 작업 프라미스에 대한 이행 함수(then) 실행
      this.queue.push(() => {
        return task().then(resolve, reject);
      });

      // 현재 이벤트 루프에서 큐의 작업을 비동기적으로 수행
      // 여기서 실행되는 next의 컨텍스트 유지를 위해 bind 사용
      process.nextTick(this.next.bind(this));
    })
  }

  // 프라미스의 순차 및 병렬 실행의 조합
  async next() {
    // 현재 진행중인 프라미스 개수보다 동시성 최대 개수가 작은 경우 실행
    while (this.running < this.concurrency && this.queue.length) {
      // task는 runTask에서 추가한 작업의 래퍼 함수
      const task = this.queue.shift();

      // 현재 작업 실행
      this.running++;
      try {
        await task();
      } finally {
        // 실행 후 다음 작업 실행
        this.running--;
        this.next();
      }
    }
  }
}

// 예제를 위한 프라미스 생성 함수
function delayResolve(milliseconds) {
  // 새로운 프라미스 반환
  return new Promise((resolve, reject) => {
    // setTimeout 비동기 함수 내에서 resolve 이행
    setTimeout(() => {
      // resolve는 현재 시간에 대한 Date 객체 반환
      console.log(`delayRosolve(${milliseconds}) is called`);
      resolve(new Date());
    }, milliseconds)
  });
}

const queue = new TaskQueue(5);
let initMilli = 4096;
for (let i=1;i<=10;i++){
  queue.runTask(async () => {
    try {
      initMilli = initMilli/2;
      return await delayResolve(initMilli);
    } catch (err) {
      console.error(err);
      process.exit(1);
    }
  })
}