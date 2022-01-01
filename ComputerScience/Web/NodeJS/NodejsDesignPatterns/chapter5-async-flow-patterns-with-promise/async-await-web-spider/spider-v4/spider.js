import { promises as fsPromises } from 'fs'; // 프라미스화한 fs 함수 접근을 위한 프라미스 객체
import { dirname } from 'path';
import superagent from 'superagent';
import { urlToFilename, getPageLinks } from '../utils.js';
import { TaskQueue } from './taskQueue.js';


// 다운로드 및 저장 프로세스를 async/await으로 동기적인 코드로 작성
// i.e 일련의 비동기 작업을 순차적으로 진행
async function download(url, filename) {
  console.log(`Downloading ${url} into ${filename}`);

  try {
    const { text: content } = await superagent.get(url);
    await fsPromises.mkdir(dirname(filename), { recursive: true });
    await fsPromises.writeFile(filename, content);

    console.log(`Downloaded and saved : ${url}`);

    // 이 ssync 함수를 호출하는 부분에서 content를 가지고 이행하는 Promise를 받음
    return content;

  } catch (err) {
    // 404 NOT Found 에 대한 예외만 처리
    if (err.status === 404) {
      return '';
    }
    throw err;
  }
}

// 동적인 일련의 비동기작업을 병렬로 수행
// 현재 페이지에 있는 링크들에 대한 크롤링
async function spiderLinks(url, body, nesting, queue) {
  // 탐색 깊이에 다다르면 현재 상태에 해당하는 프라미스 반환
  if (nesting === 0 || !body) {
    return;
  }

  // 현재 페이지의 링크들 추출
  const links = getPageLinks(url, body);

  // 각 링크에 대한 크롤링을 병렬로 진행하기 위해 각 링크 크롤링 작업에 대한 spiderTask 프라미스 생성
  const promises = links.map(link => spiderTask(link, nesting - 1, queue));

  // 실행되는 모든 프라미스에 대한 동시성 제한은 TaskQueue의 대기열 책임
  return Promise.all(promises);
}

// 파일 접근 -> 없으면 다운로드에 대한 경쟁 상태를 막기 위한 변수
const spideringFiles = new Set();

// 링크에 대한 페이지를 다운로드하는 spider 작업 정의
// 해당 링크에 대한 작업을 TaskQueue에 추가하는 프라미스 반환
async function spiderTask(url, nesting, queue) {
  // 이미 작업이 된 url의 경우 조기 종료 : 빈 프라미스 반환
  if (spideringFiles.has(url)) {
    return;
  }

  // 새로 작업하는 url의 경우 추가
  spideringFiles.add(url);

  const filename = urlToFilename(url);

  if (!filename) {
    return;
  }

  // filename에 대해서 로컬에서 읽고 이후 크롤링 작업을 하는 프라미스를 큐에 추가
  let content = await queue.runTask(async () => {
    try {
      return await fsPromises.readFile(filename, 'utf-8');
    } catch (err) {
      // 해당 파일을 읽는데 에러가 있는 경우 
      if (err.code !== 'ENOENT') {
        throw err;
      }

      // 해당 파일이 존재하지 않으면 다운로드
      return await download(url, filename);
    }
  });

  return spiderLinks(url, content, nesting, queue);
}

// TaskQueue 객체 생성 및 작업 수행
export async function spider(url, nesting, concurrency) {
  const queue = new TaskQueue(concurrency);
  return spiderTask(url, nesting, queue);
}