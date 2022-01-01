//import { spider } from "./spider-v0.js";
//import { spider } from "./spider-v1.js";
//import { spider } from "./spider-v2.js";
import { spider } from "./spider-v3.js";

const legacyUpToV1 = (url) => {
  spider(url, (err, filename, downloaded) => {
    if (err) {
      console.log('error', err);
    } else if (downloaded) {
      console.log(`Completed the downloaded of "${filename}"`);
    } else {
      console.log(`"${filename}" was already downloaded`)
    }
  });
}

const url = process.argv[2];
const nesting = process.argv[3];

spider(url, nesting, err=> {
  if (err) {
    console.error('ERROR :', err.message);
    process.exit(1);
  }


  console.log('Download Complete');
});