const express = require('express');
const User = require('../schemas/user');
const Comment = require('../schemas/comment');

const router = express.Router();

router.route('/').
    get(async (req, res, next) => {
        try {
            // DB에서 모든 유저 정보 가져와서 반환
            const users = await User.find({});
            res.json(users);
        } catch (err) {
            console.error(err);
            next(err);
        }
    })
    .post(async (req, res, next) => {
        try {
            // DB에 유저 등록
            const { name, age, married, comment } = req.body;
            const user = await User.create({
                name,
                age,
                married,
                comment
            });

            console.log(`user added : ${user}`);
            res.status(201).json(user);
        } catch (err) {
            console.error(err);
            next(err);
        }
    });

router.get('/:id/comments', async (req, res, next) => {
    try {
        // 유저 id를 이용하여 관련 댓글들 가져옴
        // JOIN과 비슷한 역할을 하는 populae 호출
        const comments = await Comment.find({commenter: req.params.id }).populate('commenter');
        console.log(`GET comments : ${comments}`);
        res.json(comments);
    } catch (err) {
        console.error(err);
        next(err);
    }
});


module.exports = router;