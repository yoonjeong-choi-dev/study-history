const request = require('supertest');
const { sequelize } = require('../models');
const app = require('../app');

// 테스트 수행 전 실행 함수 : 테스트 DB 테이블 생성
beforeAll(async () => {
    await sequelize.sync();
})

//  회원 가입 테스트 
describe('POST /join', () => {

    // 비로그인 상태에서 회원 가입 : 성공
    test('로그인 안 했으면 가입', (done) => {
        request(app)
            .post('/auth/join')
            // 전송할 데이터 정의
            .send({
                email: 'yj-test@gmail.com',
                password: 'yj-test-pw',
                nick: 'yjchoiTEST'
            })
            // 회원가입 성공 시, /로 라다이렉트
            .expect('Location', '/')
            .expect(302, done);
    });

    

    // 각 test 실행 전에 수행 하는 함수 
    // 각 test에 대해서 우선 로그인을 함 
    // => 로그인한 상태에서 다양한 테스트 수행
    const agent = request.agent(app);
    beforeEach((done) => {
        agent
            .post('/auth/login')
            .send({
                email: 'yj-test@gmail.com',
                password: 'yj-test-pw'
            })
            .end(done);
    });

    // 로그인 상태로 가입 시도 : isNotLoggedIn에서 에러가 떨어짐
    test('로그인 되어 있는 상태에서 회원 가입', (done) => {
        // 에러 메시지 : isNotLoggedIn 함수의 에러 메시지
        const message = 'Already Logged In';
        request(app)
            .post('/auth/join')
            // 전송할 데이터 정의
            .send({
                email: 'yj-test@gmail.com',
                password: 'yj-test-pw',
                nick: 'yjchoiTEST'
            })
            // 실패 시 에러 메시지와 함께 리다이렉트 : /auth/lo
            .expect('Location', `/join?error=exit`)
            .expect(302, done);
    });
});


// 로그인 테스트
describe('POST /login', () => {
    test('가입되지 않은 회원', (done) => {
        // localStrategy 에러 
        const message = encodeURIComponent('가입되지 않은 회원입니다');
        request(app)
            .post('/auth/login')
            .send({
                email: 'yj-test-wrong@gmail.com',
                password: 'yj-test-pw'
            })
            .expect('Location', `/?loginError=${message}`)
            .expect(302, done);
    });

    test('정상 로그인', (done) => {
        request(app)
            .post('/auth/login')
            .send({
                email: 'yj-test@gmail.com',
                password: 'yj-test-pw',
            })
            // 로그인 성공 시, /로 라다이렉트
            .expect('Location', '/')
            .expect(302, done);
    });

    test('비밀번호 틀림', (done) => {
        // localStrategy 에러 
        const message = encodeURIComponent('비밀번호가 일치하지 않습니다');
        request(app)
            .post('/auth/login')
            .send({
                email: 'yj-test@gmail.com',
                password: 'yj-test-pw-wrong',
            })
            .expect('Location', `/?loginError=${message}`)
            .expect(302, done);
    });
});

// 로그아웃 테스트
describe('GET /logout', () => {
    test('로그인 되어있지 않으면 403', (done) => {
      request(app)
        .get('/auth/logout')
        .expect(403, done);
    });
    
    // 로그아웃 테스트를 위해 로그인
    const agent = request.agent(app);
    beforeEach((done) => {
      agent
        .post('/auth/login')
        .send({
            email: 'yj-test@gmail.com',
            password: 'yj-test-pw',
        })
        .end(done);
    });
  
    test('로그아웃 수행', (done) => {
      agent
        .get('/auth/logout')
        // 로그아웃 성공 시, /로 라다이렉트
        .expect('Location', `/`)
        .expect(302, done);
    });
  });


// 테스트 수행 후 실행 함수 : 테스트에서 생성된 데이터들을 정리
afterAll(async () => {
    await sequelize.sync({ force: true });
});