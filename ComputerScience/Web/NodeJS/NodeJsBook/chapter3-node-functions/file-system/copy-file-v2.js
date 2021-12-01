const fs = require('fs').promises;

if (process.argv.length != 4) {
    const path = require('path');
    console.error(`usage : node ${path.basename(__filename)} <src> <dest>`);
    process.exit(1);
}

const sourceFile = process.argv[2];
const destFile = process.argv[3];

fs.copyFile(sourceFile, destFile)
    .then(()=>{
        console.log("Success to copy");
    })
    .catch(err => {
        console.error(`Fail to copy : ${err}`);
    });