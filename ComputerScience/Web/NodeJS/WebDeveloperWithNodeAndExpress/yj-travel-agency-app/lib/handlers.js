// 라우팅 핸들러
exports.api = {};

const fortune = require('./fortune');

exports.home = (req, res) => res.render('index');

exports.about = (req, res) => res.render('about', {
    fortune: fortune.getFortune(),
});

// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// newsletter 관련 
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// AJAX 호출 관련 페이지
exports.newsletter = (req, res) => {
    res.render('newsletter/newsletter', {
        csrf: 'CSRF token goes here!',
    });
};

exports.api.newsletterSignup = (req, res) => {
    // 요청 바디 체크
    console.log('CSRF token (from hidden form field): ' + req.body._csrf);
    console.log('Name (from visible form field): ' + req.body.name);
    console.log('Email (from visible form field): ' + req.body.email);

    res.send({ result: 'success' });
};

// Form Action 관련 페이지
exports.newletterSignup = (req, res) => {
    res.render('newsletter/newsletter-signup', {
        csrf: 'CSRF token goes here!',
    });
};

exports.newletterSignupProcess = (req, res) => {
    // 요청 바디 체크
    console.log('CSRF token (from hidden form field): ' + req.body._csrf);
    console.log('Name (from visible form field): ' + req.body.name);
    console.log('Email (from visible form field): ' + req.body.email);

    // 감사 페이지로 리다이렉트 : 사용자의 브라우저의 url을 깔끔하게 하기 위해
    res.redirect(303, '/newsletter-signup/thank-you')
};

exports.newletterSignupThankYou = (req, res) => {
    res.render('newsletter/newsletter-signup-thank-you');
};


// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// contest 관련
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// AJAX 호출 관련 페이지
exports.vacationPhotoContestAjax = (req, res) => {
    const curDate = new Date();
    res.render('contest/vacation-photo-ajax', {
        year: curDate.getFullYear(),
        month: curDate.getMonth(),
    });
};

exports.api.vacationPhotoContest = (req, res, fields, files) => {
    console.log('field data :', fields);
    console.log('files :', files);
    res.send({ 'result': 'success' });
};

exports.api.vacationPhotoContestError = (req, res, err) => {
    res.send({ result: 'error', error: err.message })
}

// Form Action 관련 페이지
exports.vacationPhotoContest = (req, res) => {
    const curDate = new Date();
    res.render('contest/vacation-photo', {
        year: curDate.getFullYear(),
        month: curDate.getMonth(),
    });
};

exports.vacationPhotoContestProcess = (req, res, fields, files) => {
    console.log('field data :', fields);
    console.log('files :', files);
    res.redirect(303, '/contest/vacation-photo-thank-you');
};

exports.vacationPhotoContestProcessThankYou = (req, res) => {
    res.render('contest/vacation-photo-thank-you');
};

exports.vacationPhotoContestProcessError = (req, res, err) => {
    res.render('contest/vacation-photo-error', {
        message: err.message,
    });
};

// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// 404 Not Found 관련 
// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
exports.notFound = (req, res) => {
    res.status(404);
    res.render('clientError');
};

// ESLint 와 express 미들웨어 사이의 불일치 => 해당 코드에 대해서는 eslint 무시
/* eslint-disable no-unused-vars */
exports.serverError = (err, req, res, next) => {
    console.log('===========================================');
    console.log('SERVER ERROR');
    console.log(err);
    console.log('===========================================');

    res.status(500);
    res.render('serverError');
};
/* eslint-disable no-unused-vars */
