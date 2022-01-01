// 일련의 비동기 작업을 순차적으로 처리하는 일반적인 솔루션
// task1 -> task2 -> task3 -> ... 순서로 처리해야함

// 비동기 작업
const asyncOperartion = (cb) => {
  process.nextTick(cb);
}

function task1(data, cb) {
  asyncOperartion(() => {
    const result = data + ' from task1';
    task2(result, cb);
  });
}

function task2(data, cb) {
  asyncOperartion(()=> {
    const result = data + ' from task2';
    task3(result ,cb);
  });
}

function task3(data, cb) {
  asyncOperartion(()=> {
    const result = data + ' from task3';
    console.log(`Final Result : ${result}`);
    cb();
  })
};

const data = 'Sequential Async Flow';
task1(data, () => {
  console.log('task1 -> task2 -> task3 done');
});