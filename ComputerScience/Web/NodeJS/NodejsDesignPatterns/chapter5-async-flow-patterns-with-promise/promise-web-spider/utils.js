import path from 'path';
import { URL } from 'url';
import slug from 'slug';
import cheerio from 'cheerio';

// 현재 url에 추가되는 a 태그의 href 추출
function getLinkUrl (currentUrl, element) {
  const parsedLink = new URL(element.attribs.href || '', currentUrl)
  const currentParsedUrl = new URL(currentUrl)
  if (parsedLink.hostname !== currentParsedUrl.hostname ||
    !parsedLink.pathname) {
    return null
  }
  return parsedLink.toString()
};

// url을 통해 파일 이름 추출
export function urlToFilename (url) {
  if (url.lastIndexOf('.png') !== -1 || url.lastIndexOf('.jpg') !== -1) {
    return '';
  }

  const parsedUrl = new URL(url)
  const urlPath = parsedUrl.pathname.split('/')
    .filter(function (component) {
      return component !== ''
    })
    .map(function (component) {
      return slug(component, { remove: null })
    })
    .join('/');

  let filename = path.join(parsedUrl.hostname, urlPath)
  if (!path.extname(filename).match(/htm/)) {
    filename += '.html'
  }

  return filename
}

// 현재 페이지에 있는 모든 링크 추출
export function getPageLinks(currentUrl, body) {
  // a 태그에 있는 url 리스트 
  return Array.from(cheerio.load(body)('a'))
    .map((element) => getLinkUrl(currentUrl, element))
    .filter(Boolean);
}


