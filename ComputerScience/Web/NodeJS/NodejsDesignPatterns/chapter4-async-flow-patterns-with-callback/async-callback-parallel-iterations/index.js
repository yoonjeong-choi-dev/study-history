// 무한 병렬 실행 패턴

// 다수의 반복 작업을 한 비동기 작업들
const asyncTasks = [
  (cb) => {
    console.log('Task 1 ');
    setTimeout(cb, 1000);
  },
  (cb) => {
    console.log('Task 2');
    setTimeout(cb, 1000);
  },
  (cb) => {
    console.log('Task 3');
    setTimeout(cb, 1000);
  },
];

// 비동기 작업을 병렬로 처리하는 함수
function parellalAysncTasks(tasks, finalCb) {

  // 완료된 개수
  let completedNum = 0;
  // 전체 작업 완료를 알리는 콜백 정의
  const done = () => {
    // 모두 완료된 경우 종료
    if (++completedNum === tasks.length) {
      return finalCb();
    }
  }

  tasks.map(task => task(done));
}

parellalAysncTasks(asyncTasks, () => {
  console.log('Tasks are complete');
});