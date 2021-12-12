// 테스트할 모듈
const handlers = require('../handlers');

test('Home page renders', () => {
    // req, res mocking
    const req = {};
    const res = {
        render: jest.fn(),
    };

    // 테스트 할 함수 실행
    handlers.home(req, res);

    // render 함수는 한번만 실행되어야 함
    expect(res.render.mock.calls.length).toBe(1);

    // 실행된 render에서 첫번째 인자([0][0])은 'index'여야 함
    expect(res.render.mock.calls[0][0]).toBe('index');
});

test('About page renders', () => {
    // req, res mocking
    const req = {};
    const res = {
        render: jest.fn(),
    };

    handlers.about(req, res);
    expect(res.render.mock.calls.length).toBe(1);
    expect(res.render.mock.calls[0][0]).toBe('about');

    // 추가적으로 fortune 모듈에 대한 테스트 필요
    // 2번째 인자에는 fortune 키에 한 글자 이상의 문자열이 있어야 함
    expect(res.render.mock.calls[0][1])
        .toEqual(expect.objectContaining({
            fortune: expect.stringMatching(/\W/),
        }));
});

test('NotFound page renders', () => {
    // req, res mocking
    const req = {};
    const res = {
        // 404 상태 코드 반환
        status: jest.fn(() => res),
        render: jest.fn(),
    };

    handlers.notFound(req, res);
    expect(res.render.mock.calls.length).toBe(1);
    expect(res.render.mock.calls[0][0]).toBe('clientError');
    expect(res.status).toBeCalledWith(404);
});

test('Server Error page renders', () => {
    // err, req, res, next mocking
    const err = new Error('some server error');
    const req = {};
    const res = {
        // 500 상태 코드 반환
        status: jest.fn(() => res),
        render: jest.fn(),
    };
    const next = jest.fn();

    handlers.serverError(err, req, res, next);
    expect(res.render.mock.calls.length).toBe(1);
    expect(res.render.mock.calls[0][0]).toBe('serverError');
    expect(res.status).toBeCalledWith(500);
});
