const express = require('express');

const { verifyToken, apiLimiter } = require('../../authMiddleware');
const { User } = require('../../../models');

const router = express.Router();

router.get('/follower', verifyToken, apiLimiter, (req, res) => {

    User.findOne({
        where: { id: req.decoded.id },
        include: [{
            model: User,
            attributes: ['id', 'nick'],
            as: 'Followers',
        }]
    }).then((users) => {
        res.json({
            code: 200,
            payload: users.Followers
        });
    }).catch((err) => {
        console.error(err);
        return res.status(500).json({
            code: 500,
            message: 'Server Error'
        });
    });
});

router.get('/following', verifyToken, apiLimiter, (req, res) => {

    User.findOne({
        where: { id: req.decoded.id },
        include: [{
            model: User,
            attributes: ['id', 'nick'],
            as: 'Followings',
        }]
    }).then((users) => {
        res.json({
            code: 200,
            payload: users.Followings
        });
    }).catch((err) => {
        console.error(err);
        return res.status(500).json({
            code: 500,
            message: 'Server Error'
        });
    });

});

router.get('/', verifyToken, apiLimiter, (req, res) => {

    User.findOne({
        where: { id: req.decoded.id },
        include: [{
            model: User,
            attributes: ['id', 'nick'],
            as: 'Followers',
        }, {
            model: User,
            attributes: ['id', 'nick'],
            as: 'Followings',
        }]
    }).then((users) => {
        res.json({
            code: 200,
            payload: users
        });
    }).catch((err) => {
        console.error(err);
        return res.status(500).json({
            code: 500,
            message: 'Server Error'
        });
    });

});

module.exports = router;