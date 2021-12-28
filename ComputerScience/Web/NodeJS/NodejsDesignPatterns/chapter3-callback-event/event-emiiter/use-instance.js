const { EventEmitter } = require('events');
const { readFile } = require('fs');

const findRegex = (files, regex) => {
  // 인스턴스 생성
  const emitter = new EventEmitter();
  for(const file of files) {
    readFile(file, 'utf-8', (err, content) => {
      // 에러에 대한 이벤트 생성
      if(err) {
        return emitter.emit('error', err);
      }

      // 파일을 읽는다는 이벤트 생성
      emitter.emit('fileread', file);

      const match = content.match(regex);
      if (match) {
        // 정규표현식과 일치하는 컨텐츠에 대한 이벤트 생성
        match.forEach(elem => emitter.emit('found', file, elem));
      }
    })
  }

  // 인스턴스 반환
  return emitter
};

// 이벤트 에미터에 대한 리스터 등록
findRegex(['fileA.txt', 'fileB.json'], /hello \w+/g)
 .on('fileread', file => console.log(`${file} was read`))
 .on('found', (file, match) => console.log(`Matched ${match} in ${file}`))
 .on('error', err => console.error(`Error emitted ${err.message}`));