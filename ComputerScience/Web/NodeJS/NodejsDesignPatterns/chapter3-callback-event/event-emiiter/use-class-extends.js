const { EventEmitter } = require('events');
const { readFile } = require('fs');

class FindRegex extends EventEmitter {
  constructor(regex) {
    super();
    this.regex = regex;
    this.files = [];
  }

  addFile(file) {
    this.files.push(file);
    return this;
  }

  find() {
    for (const file of this.files) {
      readFile(file, 'utf-8', (err, content) => {
        // 에러에 대한 이벤트 생성
        if (err) {
          return this.emit('error', err);
        }

        // 파일을 읽는다는 이벤트 생성
        this.emit('fileread', file);

        const match = content.match(this.regex);
        if (match) {
          // 정규표현식과 일치하는 컨텐츠에 대한 이벤트 생성
          match.forEach(elem => this.emit('found', file, elem));
        }
      })
    }

    return this;
  }
}


// 이벤트 에미터에 대한 리스터 등록
const findRegex = new FindRegex(/hello \w+/g)
  .addFile('fileA.txt')
  .addFile('fileB.json')
  .find()
  .on('fileread', file => console.log(`${file} was read`))
  .on('found', (file, match) => console.log(`Matched ${match} in ${file}`))
  .on('error', err => console.error(`Error emitted ${err.message}`));