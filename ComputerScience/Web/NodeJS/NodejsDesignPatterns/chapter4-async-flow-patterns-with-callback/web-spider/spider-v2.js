import fs from 'fs';
import path from 'path';
import superagent from 'superagent';
import { urlToFilename, getPageLinks } from './utils.js';


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

  superagent.get(url)
    .then( res => {
      if (res.status === 404) {
        return cb(new Error('Response Not FOUND'));
      }
      
      // 파일 저장
      saveFile(filename, res.text, err => {
        if (err) {
          return cb(err);
        }
        console.log(`Downloaded and saved : ${url}`);
        cb(null, res.text);
      });
    })
    .catch(err => cb(err));
}

// 순차 비동기 알고리즘을 이용하여 재귀적으로 다운로드
function spiderLinks(url, body, nesting, cb) {
  // 탐색 깊이에 다하면 조기 종료 : 동기 방식의 비동기화
  if (nesting === 0) {
    return process.nextTick(cb);
  }

  // 현재 페이지의 링크들 추출
  const links = getPageLinks(url, body);

  // 링크가 없으면 조기 종료 : 동기 방식의 비동기화
  if (links.length === 0) {
    return process.nextTick(cb);
  }

  // 재귀 함수 정의
  const recursive = (idx) => {
    if (idx === links.length) {
      // 이 경우는 모든 작업이 처리된 것으로 동기적 반환 가능
      return cb();
    }

    // 링크에 대해서 spider 호출
    // 순차적으로 비동기 연산 실행
    spider(links[idx], nesting - 1, err => {
      if (err)
        return cb(err);

      recursive(idx + 1);
    });
  }

  recursive(0);
}

// 페이지에 있는 링크들에 대해서 재귀적으로 다운로드
// nesting 변수를 이용하여 재귀 깊이 제한
export function spider(url, nesting, cb) {
  const filename = urlToFilename(url);

  // filename에 대해서 로컬에서 읽기
  fs.readFile(filename, 'utf-8', (err, fileContent) => {
    if (err) {
      // 해당 파일을 읽는데 에러가 있는 경우 조기 종료
      if (err.code !== 'ENOENT') {
        return cb(err);
      }

      // 해당 파일이 존재하지 않으면 다운로드
      return download(url, filename, (err, reqContent) => {
        if (err)
          return cb(err);

        // 다운로드된 컨텐츠에서 링크들에 대한 다운로드
        spiderLinks(url, reqContent, nesting, cb);
      })
    }

    // 파일이 이미 존재하면, 해당 파일의 링크들에 대한 다운로드
    spiderLinks(url, fileContent, nesting, cb);
  });

}