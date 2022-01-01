//import { spider } from "./spider-v2.js";
import { spider } from "./spider-v3.js";



const url = process.argv[2];
const nesting = process.argv[3] || 2;

spider(url, nesting)
  .then(()=> console.log('Download Complete'))
  .catch(err => console.error('ERROR :', err.message));