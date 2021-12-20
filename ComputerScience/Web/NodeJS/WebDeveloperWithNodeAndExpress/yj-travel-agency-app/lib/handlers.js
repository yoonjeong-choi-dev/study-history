const {VALID_EMAIL_REGEX, NewsletterSignup } = require('./newsletterSignup');

// 라우팅 핸들러
exports.api = {};

const fortune = require('./fortune');

exports.home = (req, res) => res.render('index');

exports.about = (req, res) => res.render('about', {
    fortune: fortune.getFortune(),
});

exports.cookieTest = (req, res) => {
    if (req.cookies) {
        console.log('Cookies from client :', req.cookies);
    }
    if (req.signedCookies) {
        console.log('Signed cookies from client :', req.signedCookies);
    }

    res.cookie('simple_cookie', 'This is node js!');
    res.cookie('signed_cookie', 'This is signed cookie!', {signed: true});

    res.writeHead(200, { 'Content-Type': 'text/html'});
    res.end('<h2>Check cookies in Application Tab from Developer Tools</h2>');
};

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


    // input validation : 이메일이 유효하지 않으면 플래시 메시지를 통해 사용자에게 메시지 전송
    const name = req.body.name || '';
    const email = req.body.email || '';
    if(!VALID_EMAIL_REGEX.test(email)) {
        req.session.flash = {
            type: 'danger',
            intro:'Validation Error',
            message: 'Your email address was not valid',
        };
        return res.redirect(303, '/newsletter-signup');
    }

    // 이메일 저장 인터페이스 사용 : 모의 코드
    new NewsletterSignup({name, email}).save()
        .then(() => {
            // 성공에 대한 플래시 메시지
            req.session.flash = {
                type: 'success',
                intro: 'Thank you!',
                message: 'Thanks for singing up for our newsletter!',
            };
            return res.redirect(303, '/newsletter/archive');
        })
        .catch(err => {
            // 에러에 대한 플래시 메시지
            req.session.flash = {
                type: 'danger',
                intro: 'Database Error',
                message: 'There is a problem in database. Please try again later',
            };
            return res.redirect(303, '/newsletter/archive');
        })

    // 감사 페이지로 리다이렉트 : 사용자의 브라우저의 url을 깔끔하게 하기 위해
    //res.redirect(303, '/newsletter-signup/thank-you')
};

exports.newletterSignupThankYou = (req, res) => {
    res.render('newsletter/newsletter-signup-thank-you');
};

exports.newletterSignupResult = (req, res) => {
    res.render('newsletter/newsletter-signup-developing');
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
