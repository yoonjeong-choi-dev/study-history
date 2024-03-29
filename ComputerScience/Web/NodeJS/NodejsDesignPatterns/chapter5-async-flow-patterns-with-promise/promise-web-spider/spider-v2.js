import { promises as fsPromises} from 'fs'; // 프라미스화한 fs 함수 접근을 위한 프라미스 객체
import { dirname } from 'path';
import superagent from 'superagent';
import { urlToFilename, getPageLinks } from './utils.js';


// 다운로드 및 저장 프로세스를 프라미스를 이용하여 순차적으로 진행
// i.e 일련의 비동기 작업을 순차적으로 진행
function download(url, filename) {
  console.log(`Downloading ${url} into ${filename}`);

  let content;
  
  // 여기서는 catch를 이용하여 예외 처리 X
  // 상위 스택에서 해당 예외를 처리
  return superagent.get(url)
    .then((res) => {
      // 컨텐츠 데이터 저장
      content = res.text;

      // 디렉터리 생성하는 프라미스 반환
      return fsPromises.mkdir(dirname(filename), {recursive: true});
    })
    // 디렉터리 생성 후 파일 저장
    .then(() => {
      fsPromises.writeFile(filename, content);
    })
    .then(() => {
      console.log(`Downloaded and saved : ${url}`);

      // 마지막 then에서 반환하는 값
      // 이 함수를 호출하는 부분에서 content를 가지고 이행하는 Promise를 받음
      return content;
    })
    .catch(err => {
      if (err.status === 404) {
        return '';
      }
      throw err;
    });
}

// 동적인 일련의 비동기작업을 수행하기 위해서는 프라미스 체인을 동적 생성
function spiderLinks(url, body, nesting) {
  // 정의되지 않은 빈 프라미스 정의 : 체인의 시작점
  let promise = Promise.resolve();

  // 탐색 깊이에 다다르면 현재 상태에 해당하는 프라미스 반환
  if (nesting === 0 || !body) {
    return promise;
  }

  // 현재 페이지의 링크들 추출
  const links = getPageLinks(url, body);

  // 각 링크에 대한 크롤링 진행 : 프라미스 체인을 동적으로 만드는 과정
  for (const link of links) {
    // 각 링크에 대한 크롤링이 완료될 때까지 다음 링크는 대기
    promise = promise.then(()=> spider(link, nesting-1));
  }

  return promise;
}

// 페이지에 있는 링크들에 대해서 재귀적으로 다운로드
// nesting 변수를 이용하여 재귀 깊이 제한
export function spider(url, nesting) {
  const filename = urlToFilename(url);

  if (!filename) {
    return Promise.resolve();
  }

  // filename에 대해서 로컬에서 읽고 이후 크롤링 작업을 하는 프라미스 반환
  return fsPromises.readFile(filename, 'utf-8')
    .catch(err => {
      // 해당 파일을 읽는데 에러가 있는 경우 
      if (err.code !== 'ENOENT') {
        throw err;
      }

      // 해당 파일이 존재하지 않으면 다운로드
      return download(url, filename);
    })
    // 파일이 존재하지 않은 겨우 : download 마지막 then에서 반환하는 content
    // 파일이 존재하는 경우 : readFile 함수의 resolve로 전단될 파일 content
    .then(content => spiderLinks(url, content, nesting));
}