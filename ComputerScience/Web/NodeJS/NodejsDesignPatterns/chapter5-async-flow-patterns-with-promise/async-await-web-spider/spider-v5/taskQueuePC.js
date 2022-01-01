export class TaskQueuePC {
  constructor(concurrency) {
    // 작업 큐
    this.taskQueue = [];
    
    // 사용되지 않는 소비자
    // 소비자 : 대기열에 있는 작업을 하나씩 추출하여 실행하는 주체
    // 각 소비자는 단순히 작업 이행(resolve) 비동기 함수
    this.consumerQueue = [];

    // 제어할 동시성의 개수만큼 소비자 생성
    for(let i=0;i<concurrency;i++){
      this.consumer();
    }
  }

  async consumer() {
    // 하나의 소비자는 자신이 처리할 작업이 추가될 때까지 대기 후(await), 작업 수행(task())
    while(true) {
      try {
        // getNextTask를 통해 대기열에서 새로운 작업 조회
        const task = await this.getNextTask();

        // 새로운 작업 수행
        await task();
      } catch (err) {
        console.error(err);
      }
    }
  }

  async getNextTask() {
    return new Promise((resolve) => {
      // 처리할 작업이 있는 경우 해당 작업 수행(resovle)
      if (this.taskQueue.length !== 0) {
        return resolve(this.taskQueue.shift());
      } else {
        // 비어있는 경우 : 소비자 큐에 작업 수행 함수를 저장
        // 추후 작업이 추가되면 해당 소비자가 작업 수행
        this.consumerQueue.push(resolve);
      }

    })
  }

  runTask(task) {
    return new Promise((resolve, reject) => {
      // 작업에 대한 래퍼 함수
      // 작업이 반환하는 프라미스에 대해서 이행/거부 함수 설정
      const taskWrapper = () => {
        const taskPromise = task();
        taskPromise.then(resolve, reject);
        return taskPromise;
      }
      
      // 쉬고 있는 소비자가 있는 경우 해당 프라미스 수행
      if (this.consumerQueue.length !== 0){
        // consumer : 
        const consumer = this.consumerQueue.shift();
        consumer(taskWrapper);
      } else {
        // 소비자가 가득 차있는 경우, 대기열에 저장
        this.taskQueue.push(taskWrapper);
      }
    });
  }
}