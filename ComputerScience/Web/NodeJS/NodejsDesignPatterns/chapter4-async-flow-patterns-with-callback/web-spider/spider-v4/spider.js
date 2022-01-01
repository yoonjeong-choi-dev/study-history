import fs from 'fs';
import path from 'path';
import superagent from 'superagent';
import { urlToFilename, getPageLinks } from '../utils.js';


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
    .then(res => {
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

// 순차 비동기 알고리즘을 이용하여 큐의 작업을 통해 재귀적으로 다운로드
function spiderLinks(url, body, nesting, queue) {
  // 탐색 깊이에 다하면 조기 종료 
  if (nesting === 0) {
    return;
  }

  // 현재 페이지의 링크들 추출
  const links = getPageLinks(url, body);

  // 링크가 없으면 조기 종료
  if (links.length === 0) {
    return;
  }

  // 각 링크에 대한 작업을 큐에 넣기 위해 spider 호출
  links.forEach(link => spider(link, nesting - 1, queue));
}

// 링크에 대한 페이지를 다운로드하는 spider 작업 정의
function spiderTask(url, nesting, queue, cb) {
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
        spiderLinks(url, reqContent, nesting, queue);
      })
    }

    // 파일이 이미 존재하면, 해당 파일의 링크들에 대한 다운로드
    spiderLinks(url, fileContent, nesting, queue);
    return cb();
  });
}

// 파일 접근 -> 없으면 다운로드에 대한 경쟁 상태를 막기 위한 변수
const spideringFiles = new Set();


export function spider(url, nesting, queue) {
  // 이미 작업이 된 url의 경우 조기 종료
  if (spideringFiles.has(url)) {
    return;
  }

  // 새로 작업하는 url의 경우 추가
  spideringFiles.add(url);

  // 다운로드 및 저장 작업을 큐에 추가
  queue.pushTask((done) => {
    spiderTask(url, nesting, queue, done);
  });

}