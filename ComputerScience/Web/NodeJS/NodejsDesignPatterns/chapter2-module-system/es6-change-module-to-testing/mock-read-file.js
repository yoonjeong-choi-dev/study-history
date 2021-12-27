// mocking fs : export defaut으로 객체가 익스포트 된 경우 객체의 속성 변경이 가능
// fs.readFile의 동작을 변경하여 테스트 시 사용
import fs from 'fs';

const originalReadFile = fs.readFile;
let mockedResponse = null;

const mockedReadFile = (path, cb) => {
  setImmediate(()=> {
    cb(null, mockedResponse);
  });
}

// fs.readFile의 동작을 변경
export const mockEnable = (responedWith) => {
  mockedResponse = responedWith;
  fs.readFile = mockedReadFile;
}

// fs.readFile 동작 복구
export const mockDisable = () => {
  fs.readFile = originalReadFile;
}