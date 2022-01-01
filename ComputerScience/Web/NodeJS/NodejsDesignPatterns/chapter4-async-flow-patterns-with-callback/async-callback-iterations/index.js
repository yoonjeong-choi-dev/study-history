// 순차 반복 패턴
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

// 비동기 작업을 반복하는 함수
function iterateAysncTasks(tasks, finalCb) {
  // 작업 처리를 위한 재귀 함수 정의
  const iterate = (idx) => {
    // 모든 작업 처리 시 종료
    if (tasks.length === idx) {
      return finalCb();
    }

    // 현재 작업 처리 후, 콜백으로 다음 작업에 대한 재귀 호출
    const task = tasks[idx];
    task(()=> iterate(idx+1));
  }

  iterate(0)
}

iterateAysncTasks(asyncTasks, (err) => {
  if (err) {
    console.error('Error :', err);
  }

  console.log('Tasks are complete');
});