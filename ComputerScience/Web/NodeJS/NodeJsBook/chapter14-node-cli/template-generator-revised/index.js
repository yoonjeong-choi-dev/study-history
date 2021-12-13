#!/usr/bin/env node

const { program } = require('commander');
const fs = require('fs');
const path = require('path');
const inquirer = require('inquirer');
const chalk = require('chalk');


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

  // 상위 경로부터 순차적으로 디렉터리 생성
  dirname.forEach((d, idx) => {
    // 상위 루트부터 순차적으로 path를 이어서 경로 체크
    const pathBuilder = dirname.slice(0, idx + 1).join(path.sep);

    // 해당 경로가 없으면 생성
    if (!checkExistence(pathBuilder)) {
      fs.mkdirSync(pathBuilder);
    }
  });
};


// main process
const makeTemplate = (type, fileName, dstDir) => {
  mkdirp(dstDir);
  if (type === 'html') {
    const filePath = path.join(dstDir, `${fileName}.html`);
    if (checkExistence(filePath)) {
      console.error(chalk.bold.red('File already exists'));
    } else {
      fs.writeFileSync(filePath, htmlTemplate);
      console.log(chalk.green(filePath, 'is created'));
    }
  } else if (type === 'express-router') {
    const filePath = path.join(dstDir, `${fileName}.js`);
    if (checkExistence(filePath)) {
      console.error(chalk.bold.red('File already exists'));
    } else {
      fs.writeFileSync(filePath, routerTemplate);
      console.log(chalk.green(filePath, 'is created'));
    }
  } else {
    console.error(chalk.bold.red('type must be "html" or "express-router"'));
  }
};

// program 모듈을 사용하여 cli 정의
// 버전 및 이름 정의
program
  .version('0.1.0', '-v, --version')
  .name('template-generator');

// 옵션 정의
program
  .command('template <type>')
  .usage('<type> --filename [filename] --path [path]')
  .description('Generate a template')
  .alias('tmpl')
  // filename 옵션에 대한 설정
  .option('-f, --filename [filename]', 'Have to enter "filename"', 'index')
  // path 옵션에 대한 설정
  .option('-d, --directory [path]', 'Have to enter "path" to save file', '.')
  // 실행 함수 정의
  .action((type, options) => {
    makeTemplate(type, options.filename, options.directory);
  });

// 사용자 인터렉션(with inquire) 및 인자 파싱
program
  .action((cmd, args) => {
    if (args) {
      // 인자가 없는 경우
      console.log(chalk.bold.red('Cannot find the corresponding command'));
      program.help();
    } else {
      // 각 옵션에 대해서 사용자 입력을 받음
      inquirer.prompt([{
        type: 'list',
        name: 'type',
        message: 'Select the type of a template',
        choices: ['html', 'express-router'],
      }, {
        type: 'input',
        name: 'name',
        message: 'Enter a file name',
        default: 'index',
      }, {
        type: 'input',
        name: 'directory',
        message: 'Enter a directory to save the file',
        default: '.',
      }, {
        type: 'confirm',
        name: 'confirm',
        message: 'Do you generate the template file?',
      }])
        .then((answers) => {
          if (answers.confirm) {
            makeTemplate(answers.type, answers.name, answers.directory);
            console.log(chalk.rgb(128, 128, 128)('Terminate the terminal'));
          }
        });
    }
  })
  .parse(process.argv);