const aws = require('aws-sdk');
const sharp = require('sharp');

const s3 = new aws.S3();

// 람다 호출 시 실행되는 함수
exports.handler = async (event, context, callback) => {
    // event 객체를 통해 s3 이미지 정보 가져오기
    const Bucket = event.Records[0].s3.bucket.name;
    const Key = decodeURIComponent(event.Records[0].s3.object.key);
    const filename = Key.split('/')[Key.split('/').length - 1];
    const ext = Key.split('.')[Key.split('.').length - 1];

    // sharp에서는 jpg 대신 jpeg 확장자 사용
    const requiredFormat = ext === 'jpg' ? 'jpeg' : ext;
    console.log('name', filename, 'ext', ext);

    // 이미지 변환 및 s3 업로드
    try {
        // s3에서 해당 이미지 메모리로 저장
        const s3Object = await s3.getObject({ Bucket, Key }).promise();
        console.log('original', s3Object.Body.length);

        // sharp 모듈을 이용하여 리사이징 진행
        const resizedImage = await sharp(s3Object.Body)
            .resize(200, 200, { fit: 'inside' })
            .toFormat(requiredFormat)
            .toBuffer();

        // 결과 이미지 s3 업로드
        await s3.putObject({
            Bucket,
            Key: `thumb/${filename}`,
            Body: resizedImage,
        }).promise();

        // 완료 시, 해당 이미지에 대한 key값 클라이언트로 전송
        return callback(null, `thumb/${filename}`);
    } catch (error) {
        console.error(error);
        return callback(error);
    }
}