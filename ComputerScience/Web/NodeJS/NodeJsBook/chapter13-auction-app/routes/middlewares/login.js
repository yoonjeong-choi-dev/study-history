exports.isLoggedIn = (req, res, next) => {
    // passport로 인해 추가된 요청의 isAuthenticated 메서드를 이용하여 로그인 여부 확인
    if (req.isAuthenticated()) {
        next();
    } else {
        res.redirect('/?loginError=Need to Login');
    }
};

exports.isNotLoggedIn = (req, res, next) => {
    // passport로 인해 추가된 요청의 isAuthenticated 메서드를 이용하여 로그인 여부 확인
    if(!req.isAuthenticated()) {
        next();
    } else {
        res.redirect('/');
    }
};