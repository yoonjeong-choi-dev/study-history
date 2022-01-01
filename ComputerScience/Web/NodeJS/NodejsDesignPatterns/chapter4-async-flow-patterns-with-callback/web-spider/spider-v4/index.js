import { spider } from './spider.js';
import { TaskQueue } from './taskQueue.js';

const url = process.argv[2];
const nesting = Number.parseInt(process.argv[3], 10) || 1;
const concurrency = Number.parseInt(process.argv[4], 10) || 2;

const spiderQueue = new TaskQueue(concurrency);
spiderQueue.on('error', (err) => console.error('ERROR :', err.message));
spiderQueue.on('empty', ()=>console.log('Download complete'));

spider(url, nesting, spiderQueue);
