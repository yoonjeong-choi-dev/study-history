const express = require('express');
const jwt = require('jsonwebtoken');

const { verifyToken } = require('../../authMiddleware');
const { Domain, User, Post, Hashtag } = require('../../../models');

const router = express.Router();

router.get('/my', verifyToken, (req, res) => {
    Post.findAll({
        where: {
            userId: req.decoded.id
        }
    }).then((posts) => {
        console.log(posts);
        res.json({
            code: 200,
            payload: posts
        });
    }).catch((err) => {
        console.error(err);
        return res.status(500).json({
            code: 500,
            message: 'Server Error'
        });
    });
});

router.get('/hashtag/:title', verifyToken, async (req, res) => {
    try {
        const hashtag = await Hashtag.findOne({where: {title: req.params.title}});
        if (!hashtag) {
            return res.status(404).json({
                code: 404,
                message: `No result for ${req.params.title}`
            });
        }

        const posts = await hashtag.getPosts();
        return res.json({
            code: 200,
            payload: posts
        });
    } catch (err) {
        console.log(err);
        return res.status(500).json({
            code: 500,
            message: 'Server Error for hashtag'
        });
    }
});



module.exports = router;