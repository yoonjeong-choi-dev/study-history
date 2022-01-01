// 동시성 제한 

// 다수의 반복 작업을 한 비동기 작업들
const asyncTasks = [
  (cb) => {
    setTimeout(()=> {
      console.log('Task 1 ');
      cb();
    }, 1500);
  },
  (cb) => {
    setTimeout(()=> {
      console.log('Task 2 ');
      cb();
    }, 300);
  },
  (cb) => {
    setTimeout(()=> {
      console.log('Task 3 ');
      cb();
    }, 300);
  },
  (cb) => {
    setTimeout(()=> {
      console.log('Task 4 ');
      cb();
    }, 300);
  },
  (cb) => {
    setTimeout(()=> {
      console.log('Task 5 ');
      cb();
    }, 1500);
  },
  (cb) => {
    setTimeout(()=> {
      console.log('Task 6 ');
      cb();
    }, 1500);
  },
];

// 비동기 작업을 병렬로 처리하는 함수
function parellalAysncTasks(maxConcurrency, tasks, finalCb) {

  // 완료된 개수와 및 현재 진행중인 동시성 개수
  let running = 0;
  let completedNum = 0;
  let idx = 0;
  
  // 순차 실행 및 병렬 실행 혼합
  const next = () => {
    // 동시성 제한 내에서 가능한 많은 작업을 병렬로 생성
    while (running < maxConcurrency && idx < tasks.length) {
      const task = tasks[idx++];
      task(()=> {
        // 이 부분은 무한 병렬 실행 패턴의 콜백과 동일
        if(++completedNum === tasks.length) {
          return finalCb();
        }

        // 완료 콜백 : 완료되었으므로 새로운 작업 실행
        console.log(`This task is done. New task will run....`);
        running--;
        next();
      })
    }
  }
  next();
}

parellalAysncTasks(2, asyncTasks, () => {
  console.log('Tasks are complete');
});