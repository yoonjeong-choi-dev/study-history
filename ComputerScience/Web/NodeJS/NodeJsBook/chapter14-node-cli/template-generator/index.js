#!/usr/bin/env node

if (process.argv.length != 5) {
  const path = require('path');
  console.error(`usage : ${path.basename(process.argv[1])} <html|express-router> <name> <path>`);
  process.exit(1);
}

const fs = require('fs');
const path = require('path');

const type = process.argv[2];
const fileName = process.argv[3];
const dstDir = process.argv[4];

if (type !== 'html' && type !== 'express-router') {
  const path = require('path');
  console.error(`usage : ${path.basename(process.argv[1])} <html|express-router> <name> <path>`);
  process.exit(1);
}

const htmlTemplate = `
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8" />
    <title>Template</title>
  </head>
  <body>
    <h1>Template Generator</h1>
    <p>YJ</p>
  </body>
</html>
`;

const routerTemplate = `
const express = require('express');
const router = express.Router();
 
router.get('/', (req, res, next) => {
   try {
     res.send('ok');
   } catch (error) {
     console.error(error);
     next(error);
   }
});
 
module.exports = router;
`;


// 디렉터리 존재 여부 확인 함수
const checkExistence = (dir) => {
  try {
    fs.accessSync(dir, fs.constants.F_OK | fs.constants.R_OK | fs.constants.W_OK);
    return true;
  } catch (err) {
    return false;
  }
};

// 경로 생성 함수
const mkdirp = (dir) => {
  // 상대 경로의 루트부터 하위 디렉터리 
  const dirname = path.relative('.', path.normalize(dir))
    .split(path.sep)
    .filter(p => !!p);
  console.log(dirname);
  // 상위 경로부터 순차적으로 디렉터리 생성
  dirname.forEach((d, idx) => {
    // 상위 루트부터 순차적으로 path를 이어서 경로 체크
    const pathBuilder = dirname.slice(0, idx + 1).join(path.sep);

    // 해당 경로가 없으면 생성
    if (!checkExistence(pathBuilder)) {
      console.log(pathBuilder, ' is created');
      fs.mkdirSync(pathBuilder);
    }
  });
};


// main process
mkdirp(dstDir);
if (type === 'html') {
  const filePath = path.join(dstDir, `${fileName}.html`);
  if (checkExistence(filePath)) {
    console.error('File already exists');
  } else {
    fs.writeFileSync(filePath, htmlTemplate);
    console.log(filePath, ' is created');
  }
} else if (type === 'express-router') {
  const filePath = path.join(dstDir, `${fileName}.js`);
  if (checkExistence(filePath)) {
    console.error('File already exists');
  } else {
    fs.writeFileSync(filePath, routerTemplate);
    console.log(filePath, ' is created');
  }
};