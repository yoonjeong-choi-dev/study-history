import fs from 'fs';
import path from 'path';
import superagent from 'superagent';
import { urlToFilename } from './utils.js';

// 콜백 지옥에 빠진 함수
export function spider(url, cb) {
  const filename = urlToFilename(url);

  // filename에 대해서 로컬에서 접근
  fs.access(filename, (err) => {
    // 해당 파일이 없으면 다운로드
    if(err && err.code ==='ENOENT') {
      console.log(`Downloading ${url} into ${filename}`);
      superagent.get(url).end((err, res) => {
        if (err) {
          cb(err);
        } else {
          // 다운로드 파일 저장을 위한 파일 생성
          fs.mkdir(path.dirname(filename), {recursive: true}, err => {
            if(err) {
              cb(err);
            } else {
              // 파일 저장
              fs.writeFile(filename, res.text, err=> {
                if(err) {
                  cb(err);
                } else {
                  cb(null, filename, true);
                }
              })
            }
          })
        }
      })
    } else {
      // 해당 파일이 있으면 다운 x
      cb(null, filename, false);
    }
  })
}