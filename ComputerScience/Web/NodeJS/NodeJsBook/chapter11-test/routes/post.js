const express = require('express');
const multer = require('multer');
const path = require('path');
const fs = require('fs');

const { sequelize, Post, Hashtag } = require('../models');
const { isLoggedIn } = require('./authMiddleware');

const router = express.Router();

// 업로드 스토리지 생성
try {
    fs.readdirSync('uploads');
} catch (err) {
    console.log('Create uploads directory');
    fs.mkdirSync('uploads');
}

const upload = multer({
    storage: multer.diskStorage({
        destination(req, file, cb) {
            cb(null, 'uploads/');
        },
        filename(req, file, cb) {
            const ext = path.extname(file.originalname);
            cb(null, path.basename(file.originalname, ext) + Date.now() + ext);
        },
    }),
    limits: { fileSize: 10 * 1024 * 1024 },
});

router.post('/img', isLoggedIn, upload.single('img'), (req, res) => {
    res.json({ url: `/img/${req.file.filename}` });
});

// 실제 멀티파트 폼에서 요청하는 데이터에는 이미지 파일이 없음
// 이미지 리소스 경로가 전송됨
const fakeUpload = multer();

router.post('/', isLoggedIn, fakeUpload.none(), async (req, res, next) => {
    try {
        const post = await Post.create({
            content: req.body.content,
            img: req.body.url,
            UserId: req.user.id
        });

        // 해시 태그 추출 및 저장
        const hashtags = req.body.content.match(/#[^\s#]+/g);
        if (hashtags) {
            const result = await Promise.all(
                hashtags.map(tag => {
                    return Hashtag.findOrCreate({
                        where: {
                            title: tag.slice(1).toLowerCase()
                        },
                    });
                }),
            );

            // 해시 태그를 post와 연결
            await post.addHashtags(result.map(r => r[0]));
        }
        res.redirect('/');
    } catch (err) {
        next(err);
    }
});

router.delete('/:id', isLoggedIn, async (req, res, next) => {
    try {
        const postId = req.params.id;

        const { UserLikesPost, PostHashtag } = sequelize.models;


        await Post.destroy({
            where: {
                id: postId
            }
        });
        await PostHashtag.destroy({
            where: {
                PostId: postId
            }
        });
        await UserLikesPost.destroy({
            where: {
                PostId: postId
            }
        });
        req.method = 'GET'
        res.redirect(303, '/');

    } catch (err) {
        console.log("Delete Post ", err);
        next(err);
    }
});

module.exports = router;