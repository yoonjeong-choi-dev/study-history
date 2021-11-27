const express = require('express');
const Comment = require('../schemas/comment');

const router = express.Router();


router.post('/', async (req, res, next) => {
    try {
        // DB에 댓글 등록
        const { id, comment } = req.body;
        const newComment = await Comment.create({
            commenter: id,
            comment
        });

        // 댓글과 유저 연결
        const result = await Comment.populate(newComment, {path: 'commenter'});
        res.status(201).json(result);
    } catch (err) {
        console.log(err);
        next(err);
    }
});

router.route('/:id')
    .patch(async (req, res, next) => {
        try {
            // 댓글 수정
            const { id } = req.params;
            const { comment } = req.body;
            
            const result = await Comment.update({
                _id: id
            }, {
                comment
            });

            res.json(result);
        } catch (err) {
            console.log(err);
            next(err);
        }
    })
    .delete(async (req, res, next) => {
        try {
            // 댓글 삭제
            const { id } = req.params;

            const result = await Comment.remove({
                _id: id
            });

            res.json(result);
        } catch (err) {
            console.log(err);
            next(err);
        }
    })

module.exports = router;