const fs = require('fs');

if (process.argv.length != 4) {
    const path = require('path');
    console.error(`usage : node ${path.basename(__filename)} <src> <dest>`);
    process.exit(1);
}

const sourceFile = process.argv[2];
const destFile = process.argv[3];

const readStream = fs.createReadStream(sourceFile);
const writeStream = fs.createWriteStream(destFile);

readStream.on('error', (err)=> {
    console.error(`Fail to create ReadStream : ${err}`);})
    .pipe(writeStream);