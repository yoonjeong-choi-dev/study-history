// 유닛 테스트 
const { isLoggedIn, isNotLoggedIn } = require('./authMiddleware');

describe('isLoggedIn', () => {
    // res 모킹 : status는 체이닝이 가능해야 하므로 자기 자신을 다시 반환
    const res = {
        status: jest.fn(()=> res),
        send: jest.fn()
    };

    // next 모킹
    const next = jest.fn();

    test('로그인이 되어 있으면 isLoggedIn이 next 호출', () => {
        // req를 로그인 상태로 모킹
        const req = {
            isAuthenticated : jest.fn(()=> true)
        };

        isLoggedIn(req, res, next);
        expect(next).toBeCalledTimes(1);
    });

    test('로그인이 되어 있지 않으면 isLoggedIn이 에러를 응답', () => {
        // req를 비로그인 상태로 모킹
        const req = {
            isAuthenticated : jest.fn(()=> false)
        };

        isLoggedIn(req, res, next);
        expect(res.status).toBeCalledWith(403);
        expect(res.send).toBeCalledWith('Need to Login');
    });
})


describe('isNotLoggedIn', () => {
    // res 모킹 : status는 체이닝이 가능해야 하므로 자기 자신을 다시 반환
    const res = {
        redirect: jest.fn()
    };

    // next 모킹
    const next = jest.fn();

    test('로그인이 되어 있으면 isNotLoggedIn이 에러를 응답', () => {
        // req를 로그인 상태로 모킹
        const req = {
            isAuthenticated : jest.fn(()=> true)
        };

        isNotLoggedIn(req, res, next);

        const message = encodeURIComponent('Already Logged In');
        expect(res.redirect).toBeCalledWith(`/?error=${message}`);
    });

    test('로그인이 되어 있지 않으면 isNotLoggedIn이 next 호출', () => {
        // req를 로그인 상태로 모킹
        const req = {
            isAuthenticated : jest.fn(()=> false)
        };

        isNotLoggedIn(req, res, next);
        expect(next).toBeCalledTimes(1);
    });
})