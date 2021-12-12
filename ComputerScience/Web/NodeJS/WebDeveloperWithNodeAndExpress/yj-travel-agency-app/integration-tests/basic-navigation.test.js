const portfinder = require('portfinder');
const puppeteer = require('puppeteer');

// 테스트 할 서버 앱 
const app = require('../index');

let server = null;
let port = null;

// 각 테스트 실행 전에 서버 시작
beforeEach(async () => {
    // 테스트 할 때 사용할 포트 찾기
    port = await portfinder.getPortPromise();

    // 해당 포트로 서버 시작
    server = app.listen(port);
});

// 각 테스트 실행 후에 서버 종료
afterEach(() => {
    server.close();
});


test('home page links to about page', async () => {
    // 헤드리스 크롬 객체(UI 없는 브라우저)
    const browser = await puppeteer.launch();
    const page = await browser.newPage();

    // 메인 페이지로 이동
    await page.goto(`http://localhost:${port}`);

    // 네비게이션 및 클릭 실행
    await Promise.all([
        page.waitForNavigation(),
        page.click('[data-test-id="about"]'),      // index.handlebar에서 정의한 데이터 속성
    ]);

    // about 페이지로 이동 검증
    expect(page.url()).toBe(`http://localhost:${port}/about`)

    // 브라우저 종료
    await browser.close();
});
