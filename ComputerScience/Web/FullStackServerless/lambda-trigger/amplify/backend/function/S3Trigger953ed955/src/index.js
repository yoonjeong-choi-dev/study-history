// eslint-disable-next-line

const sharp = require("sharp");
const aws = require("aws-sdk");
const s3 = new aws.S3();

exports.handler = async function (event) {
  // 이벤트 타입이 삭제인 경우 : 함수 종료
  if (event.Records[0].eventName === 'ObjectRemoved:Delete') return

  // 버킷 이름과 키를 이벤트에서 가져옴
  const BUCKET = event.Records[0].s3.bucket.name
  const KEY = event.Records[0].s3.object.key

  // 데이터를 가져와서 리사이징
  try {
    // 사진이 저장된 버킷에서 저장된 사진 로드
    let image = await s3.getObject({ Bucket: BUCKET, Key: KEY }).promise();
    image = await sharp(image.Body);

    // 이미지 메타 데이터
    const metadata = await image.metadata();
    if (metadata.width > 1000) {
      const resizedImage = await image.resize({width: 1000}).toBuffer();
      const resizeKey = "resized_" + Date.now();

      await s3.putObject({Bucket: BUCKET, Key: resizeKey, Body: resizedImage}).promise();
    }
    return;
  }
  catch (e) {
    console.log("Fail to load file: ", e);
  }

};
