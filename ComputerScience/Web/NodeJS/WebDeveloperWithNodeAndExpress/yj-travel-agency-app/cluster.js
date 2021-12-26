const cluster = require('cluster');
const {startServer} = require('./index');

const startWorker = () => {
  const worker = cluster.fork();
  console.log(`CLUSTER: Worker ${worker.id} started`);
}


if (cluster.isMaster) {
  // 마스터 노드인 경우 : cpu 코어 개수만큼 워커 노드 생성
  require('os').cpus().forEach(startWorker);

  // 연결이 끊어진 워커 노드 로깅
  cluster.on('disconnect', worker => console.log(`CLUSTER: Workder ${worker.id} disconnected`));

  // 워커가 종료되면 새로운 워커 생성
  cluster.on('exit', (worker, code, signal) => {
    console.log(
      `CLUSTER: Worker ${worker.id} died with exit code ` +
      `${code} (${signal})`
    );

    startWorker();
  })
} else {
  // 워커 노드는 서버 실행
  const port = process.env.PORT || 7166;
  startServer(port);
}
