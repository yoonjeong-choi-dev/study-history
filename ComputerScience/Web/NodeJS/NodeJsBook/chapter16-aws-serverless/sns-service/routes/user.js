const express = require('express');

const { isLoggedIn } = require('./authMiddleware');
const { addFollowing, deleteFollowing} = require('../controllers/user');

const { sequelize  } = require('../models');
const User = require('../models/user');
const router = express.Router();

// {id} 유저 팔로우 
router.post('/:id/follow', isLoggedIn, addFollowing);

// {id} 유저 언팔로우
router.delete('/:id/follow', isLoggedIn, deleteFollowing);

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