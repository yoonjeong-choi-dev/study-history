const express = require('express');
const { isLoggedIn, isNotLoggedIn } = require('./authMiddleware');
const {sequelize, Post, User, Hashtag} = require('../models');

const router = express.Router();

router.use((req, res, next) => {
    // res.locals의 정보들은 템플릿 엔진 전체에서 사용
    // 렌더링을 위한 데이터 설정 후, 다음 미들웨어로 넘김
    res.locals.user = req.user;
    res.locals.followerCount = req.user ? req.user.Followers.length : 0;
    res.locals.followingCount = req.user ? req.user.Followings.length : 0;
    res.locals.followerIdList = req.user ? req.user.Followings.map(f => f.id) : [];
    next();
});

// 프로필 페이지는 로그인한 경우만 보여준다
router.get('/profile', isLoggedIn, (req, res) => {
    res.render('profile', { title: `NodeTwitter - User Info` });
});

// 회원가입 페이지는 비로그인시에만 보여준다
router.get('/join', isNotLoggedIn, (req, res) => {
    res.render('join', { title: 'NodeTwitter 회원 가입' });
});

// 게시글들 출력
router.get('/', async (req, res, next) => {
    try {
        const posts = await Post.findAll({
            where: {
                deletedAt: null
            },
            include: {
                model: User,
                attributes: ['id', 'nick'],
            },
            order: [['createdAt', 'DESC']]
        });

        // 좋아요 여부 확인
        if (req.isAuthenticated()) {
            const {UserLikesPost} =  sequelize.models;

            const likes = await UserLikesPost.findAll({
                where: {UserId: req.user.id},
                attributes: ['PostId'],
            });

            posts.map(post => {
                likes.map(like => {
                    if (post.id === like.PostId) {
                        post.liked = true;
                        return;
                    }
                })
            })
        }

        res.render('main', {
            title: 'NodeTwitter',
            twits: posts
        });
    } catch (err) {
        next(err);
    }
});

// 해시태그 검색
router.get('/hashtag', async (req, res, next) => {
    const query = req.query.hashtag;
    if (!query) {
        return res.redirect('/');
    }

    try{
        const hashtag = await Hashtag.findOne({where: {title: query}});
        let posts = [];
        if (hashtag) {
            posts = await hashtag.getPosts({
                include: [{
                    model: User
                }]
            });
        }

        res.render('main', {
            title: 'NodeTwitter',
            twits: posts
        });
    } catch (err){
        return next(err);
    }
})

module.exports = router;