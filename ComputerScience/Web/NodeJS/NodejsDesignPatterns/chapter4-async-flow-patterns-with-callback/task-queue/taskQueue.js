const { EventEmitter } = require('events');

module.exports =  class TaskQueue extends EventEmitter {
  constructor(concurrency) {
    super();

    // 동시성 제한 개수
    this.concurrency = concurrency || 2;

    // 작업 큐 및 현재 진행 중인 작업의 개수
    this.queue = [];
    this.running = 0;
  }

  pushTask(task) {
    this.queue.push(task);

    // 현재 이벤트 루프에서 큐의 작업 진행
    // 여기서 실행되는 next의 컨텍스트 유지를 위해 bind 사용
    process.nextTick(this.next.bind(this));
    return this;
  }

  next() {
    // 모두 완료된 경우 이벤트 발생
    if(this.running===0 && this.queue.length === 0) {
      this.emit('empty');
    }

    // handling-parallel-tasks의 next와 동일한 작업
    while(this.running < this.concurrency && this.queue.length) {
      const task = this.queue.shift();
      task((err)=> {
        // 에러 발생 시, 이벤트 발생
        if (err) {
          this.emit('error', err);
        }
        
        // 완료 시, 다음 작업 실행
        this.running--;
        process.nextTick(this.next.bind(this));
      });

      this.running++;
    }
  }
}