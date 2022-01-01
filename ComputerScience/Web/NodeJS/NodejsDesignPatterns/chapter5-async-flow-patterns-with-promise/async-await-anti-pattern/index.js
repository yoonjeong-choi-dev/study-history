// 에러를 발생시키는 프라미스 반환 함수
function delayError(milliseconds) {
  return new Promise((resolve, reject) => {
    // setTimeout 비동기 함수 내에서 resolve 이행
    setTimeout(()=> {
      // resolve는 현재 시간에 대한 Date 객체 반환
      reject(new Error(`Error atfer ${milliseconds}s`));
    }, milliseconds)
  });
}

// async 함수는 항상 프라미스 반환
// return 값은 resolve로 전달
async function antiPattern() {
  try {
    return delayError(1000);
  } catch (err) {
    console.error(`Error never caught by async function : ${err.message}`);
  }
}

async function antiPatternCorrected() {
  try {
    return await delayError(1000);
  } catch (err) {
    console.error(`Error caught by async function : ${err.message}`);
  }
}

antiPattern().catch(err => console.error(`Error caught by caller : ${err.message}`));
antiPatternCorrected().catch(err => console.error(`Error caught by caller : ${err.message}`));