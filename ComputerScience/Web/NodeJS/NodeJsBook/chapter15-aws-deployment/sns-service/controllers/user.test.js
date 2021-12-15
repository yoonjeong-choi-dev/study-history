// User 모델 모킹
jest.mock('../models/user');
const User = require('../models/user');

const { addFollowing, deleteFollowing} = require('./user');

describe('addFollowing', () => {
    const req = {
        user: {id: 1},
        params: {id: 2}
    };

    const res = {
        status: jest.fn(()=> res),
        send: jest.fn()
    };

    const next = jest.fn();

    test('대상이 있으면 팔로잉 추가하고, success 응답', async () => {
        User.findOne.mockReturnValue(Promise.resolve({
            addFollowing(id) {
                return Promise.resolve(true);
            }
        }));

        await addFollowing(req, res, next);
        expect(res.send).toBeCalledWith('success');
    });

    test('대상이 없으면, res.status(404).send(no user) 응답', async () => {
        User.findOne.mockReturnValue(null);

        await addFollowing(req, res, next);
        expect(res.status).toBeCalledWith(404);
        expect(res.send).toBeCalledWith('no user');
    });

    test('DB에서 에러 발생 시, next(err) 호출', async () => {
        const error = 'Error for Test';
        User.findOne.mockReturnValue(Promise.reject(error));

        await addFollowing(req, res, next);
        expect(next).toBeCalledWith(error);
    });
});

describe('deleteFollowing', () => {
    const req = {
        user: {id: 1},
        params: {id: 2}
    };

    const res = {
        status: jest.fn(()=> res),
        send: jest.fn()
    };

    const next = jest.fn();

    test('대상이 있으면 팔로잉 삭제하고, success 응답', async () => {
        User.findOne.mockReturnValue(Promise.resolve({
            removeFollowing(id) {
                return Promise.resolve(true);
            }
        }));

        await deleteFollowing(req, res, next);
        expect(res.send).toBeCalledWith('success');
    });

    test('대상이 없으면, res.status(404).send(no user) 응답', async () => {
        User.findOne.mockReturnValue(null);

        await deleteFollowing(req, res, next);
        expect(res.status).toBeCalledWith(404);
        expect(res.send).toBeCalledWith('no user');
    });

    test('DB에서 에러 발생 시, next(err) 호출', async () => {
        const error = 'Error for Test';
        User.findOne.mockReturnValue(Promise.reject(error));
        
        await deleteFollowing(req, res, next);
        expect(next).toBeCalledWith(error);
    });
});