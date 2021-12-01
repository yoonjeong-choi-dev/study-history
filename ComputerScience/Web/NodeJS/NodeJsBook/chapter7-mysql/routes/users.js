const express = require('express');
const User = require('../models/user');
const Comment = require('../models/comment');

const router = express.Router();

router.route('/').
    get(async (req, res, next) => {
        try {
            // DB에서 모든 유저 정보 가져와서 반환
            const users = await User.findAll();
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
                comment: (comment) ? comment : null
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
        const comments = await Comment.findAll({
            include: {
                model: User,
                where: { id: req.params.id },
            }
        });
        console.log(comments);
        res.json(comments);
    } catch (err) {
        console.error(err);
        next(err);
    }
});


module.exports = router;