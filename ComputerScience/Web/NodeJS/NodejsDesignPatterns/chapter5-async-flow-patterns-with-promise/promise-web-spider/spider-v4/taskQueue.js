export class TaskQueue {
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
  next() {
    // 현재 진행중인 프라미스 개수보다 동시성 최대 개수가 작은 경우 실행
    while (this.running < this.concurrency && this.queue.length) {
      // task는 runTask에서 추가한 작업의 래퍼 함수
      const task = this.queue.shift();

      // 각 작업이 끝날 때, 다음 작업 실행
      // task()는 프라미스 반환
      task().finally(() => {
        this.running--;
        this.next();
      })

      this.running++;
    }
  }
}