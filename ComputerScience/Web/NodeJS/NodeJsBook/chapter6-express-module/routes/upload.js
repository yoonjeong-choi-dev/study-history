const express = require('express');
const multer = require('multer');   // 멀티파트 형식 업로드 모듈
const fs = require('fs');
const path = require('path');

// 파일 업로드 디렉터리 생성
const uploadPath = path.join(process.cwd(), 'public', 'uploads');

try {
    fs.readdirSync(uploadPath);
} catch (err) {
    console.error(`Create a directory : ${uploadPath}`);
    fs.mkdirSync(uploadPath);
}

// 멀티파트 저장을 위한 multer 설정
const uploadFile = multer({
    storage: multer.diskStorage({
        destination(req, file, done) {
            done(null, uploadPath);
        },
        filename(req, file, done) {
            console.log(req.body);
            const ext = path.extname(file.originalname);
            done(null, path.basename(file.originalname, ext) + Date.now() + ext);
        }
    }),
    limits: {
        fileSize: 10 * 1024 * 1024
    }
});

const router = express.Router();
router.get('/', (req, res, next) => {
    // 비밀 쿠키 설정
    res.cookie('method', 'upload', {
        expires: new Date(Date.now() + 90000),
        httpOnly: true,
        secure: true,
        signed: true
    });

    res.render('upload', {
        title: 'Express Server',
        host: req.headers.host,
        name: "YJ"
    });
});

router.post('/', uploadFile.single('image'), (req, res) => {
    console.log(req.file, req.body);

    // 해당 이미지로 리다이렉트
    const static_path = path.join('uploads', req.file.filename);
    res.redirect(static_path);
});

module.exports = router;