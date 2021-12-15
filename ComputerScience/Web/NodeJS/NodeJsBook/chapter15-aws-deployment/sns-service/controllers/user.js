const User = require('../models/user');

exports.addFollowing = async (req, res, next) => {
    try {
        // 팔로우할 유저 검색
        const user = await User.findOne({
            where: { id: req.user.id }
        });

        if (user) {
            await user.addFollowing(parseInt(req.params.id, 10));
            res.send('success');
        } else {
            res.status(404).send('no user');
        }
    } catch (err) {
        next(err);
    }
};

exports.deleteFollowing = async (req, res, next) => {
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
};