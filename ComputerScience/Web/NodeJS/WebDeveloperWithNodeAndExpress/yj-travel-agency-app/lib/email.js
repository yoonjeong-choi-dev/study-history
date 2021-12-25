const nodemailer = require('nodemailer');
const nodemailerSG = require('nodemailer-sendgrid');
const htmlToFormattedText = require('html-to-formatted-text');

const from = '"Yoonjeong Choi" <yjchoi7166@naver.com>'

module.exports = () => {
    // 센드그리드 api를 이용하여 nodemailer 인스턴스 생성
    const mailTransport = nodemailer.createTransport(
        nodemailerSG({
            apiKey: process.env.SENDGRID_API
        })
    );

    return (to, subject, html) => new Promise((resolve, reject) => {
        mailTransport.sendMail({
            from,
            to,
            subject,
            html,
            text: htmlToFormattedText(html),
        })
        .then(info => resolve(info))
        .catch(err => reject(err))
    });
};