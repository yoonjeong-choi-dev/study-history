import fs from 'fs';
import { mockEnable, mockDisable } from "./mock-read-file.js";

// fs의 readFile 동작 변경
mockEnable(Buffer.from('Hello Wolrd'));

// 테스트 실행
fs.readFile('fake-path', (err, data) => {
  if (err) {
    console.error(err);
    process.exit(1);
  }

  console.log(data.toString());
});

// fs의 readFile 동작 복구
mockDisable();