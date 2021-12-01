const express = require('express');


const { isLoggedIn } = require('./authMiddleware');
const { sequelize  } = require('../models');
const User = require('../models/user');
const router = express.Router();

// {id} 유저 팔로우 
router.post('/:id/follow', isLoggedIn, async (req, res, next) => {
    try {
        // 팔로우할 유저 검색
        const user = await User.findOne({
            where: {id: req.user.id}
        });

        if (user){
            await user.addFollowing(parseInt(req.params.id, 10));
            res.send('success');
        } else {
            res.status(404).send('no user');
        }
    } catch (err) {
        next(err);
    }
});

// {id} 유저 언팔로우
router.delete('/:id/follow', isLoggedIn, async (req, res, next) => {
    try {
        // 언팔로우 유저 검색
        const user = await User.findOne({
            where: {id: req.user.id}
        });

        if (user){
            await user.removeFollowing(parseInt(req.params.id, 10));
            res.send('success');
        } else {
            res.status(404).send('no user');
        }
    } catch (err) {
        next(err);
    }
});

router.post('/:id/like', isLoggedIn, async(req, res, next) => {
    try{
        // 좋아요 누를 게시글 검색
        const {postId, isLike} = req.body;
        const userId = req.user.id;

        const {UserLikesPost} =  sequelize.models;
        const userLikePost = await UserLikesPost.findOne({
            where: {
                UserId: userId,
                PostId: postId
            }
        });

        if ( isLike && !userLikePost ) {
            await UserLikesPost.create({
                UserId: userId,
                PostId: postId
            });
        } else if( !isLike && userLikePost) {
            await UserLikesPost.destroy({
                where: {
                    UserId: userId,
                    PostId: postId
                }
            });
        }
        

        return res.status(200).send('success');
    } catch (err) {
        console.log('like', err);
        next(err);
    }
});

module.exports = router;