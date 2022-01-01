import fs from 'fs';
import path from 'path';
import superagent from 'superagent';
import { urlToFilename } from './utils.js';

// 콜백 지옥에 빠진 함수 개선
// 1. 에러 발생 시, return으로 조기 종료
// 2. 콜백을 익명 함수가 아닌 명명된 함수로 생성

function saveFile(filename, contents, cb) {
  // 다운로드 파일 저장을 위한 파일 생성
  fs.mkdir(path.dirname(filename), { recursive: true }, err => {
    // 에러가 있으면 조기 종료
    if (err) {
      return cb(err);
    } 
    fs.writeFile(filename, contents, cb);
  });
}

function download(url, filename, cb) {
  console.log(`Downloading ${url} into ${filename}`);

  superagent.get(url).end((err, res) => {
    // 에러가 있으면 조기 종료
    if (err)
      return cb(err);

    // 파일 저장
    saveFile(filename, res.text, err => {
      if (err) {
        return cb(err);
      }
      console.log(`Downloaded and saved : ${url}`)
      cb(null, res.text);
    });
  });
}

export function spider(url, cb) {
  const filename = urlToFilename(url);

  // filename에 대해서 로컬에서 접근
  fs.access(filename, (err) => {
    // 해당 파일이 존재하면 조기 종료
    if (!err || err.code !=='ENOENT')
      return cb(null, filename, false);

    // 해당 파일이 없으면 다운로드
    download(url, filename, err => {
      if (err)
        return cb(err);
      
        cb(null, filename, true);
    })
  });
}