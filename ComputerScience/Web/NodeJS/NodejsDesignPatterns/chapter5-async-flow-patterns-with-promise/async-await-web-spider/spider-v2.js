import { promises as fsPromises } from 'fs'; // 프라미스화한 fs 함수 접근을 위한 프라미스 객체
import { dirname } from 'path';
import superagent from 'superagent';
import { urlToFilename, getPageLinks } from './utils.js';


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

// 동적인 일련의 비동기작업을 수행하기 위해서는 단순히 각 작업에 대해 await 이용
async function spiderLinks(url, body, nesting) {
  // 탐색 깊이에 다다르면 조기 종료
  if (nesting === 0 || !body) {
    return;
  }

  // 현재 페이지의 링크들 추출
  const links = getPageLinks(url, body);

  // 각 링크에 대한 크롤링 진행
  // 하나의 링크에 대해 크롤링이 완료될 때까지 대기
  for (const link of links) {
    await spider(link, nesting-1);
  }
  
  // 안티패턴 : forEach에 의해 spider가 반환하는 프라미스가 무시
  // => 순차 실행이 아닌 병렬 실행
  // links.forEach(async (link) => await spider(link, nesting -1));

}

// 페이지에 있는 링크들에 대해서 재귀적으로 다운로드
// nesting 변수를 이용하여 재귀 깊이 제한
export async function spider(url, nesting) {
  const filename = urlToFilename(url);

  if (!filename) {
    return;
  }

  let content;
  // filename에 대해서 로컬에서 읽고 이후 크롤링 작업
  try{
    content = await fsPromises.readFile(filename, 'utf-8');
  } catch (err) { 
    // 해당 파일을 읽는데 에러가 있는 경우 
    if (err.code !== 'ENOENT') {
      throw err;
    }

    // 해당 파일이 존재하지 않으면 다운로드
    content = await download(url, filename);
  }

  return spiderLinks(url, content, nesting);
}