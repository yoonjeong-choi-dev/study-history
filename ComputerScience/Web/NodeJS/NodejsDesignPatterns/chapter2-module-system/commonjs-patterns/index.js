const namedExports = require('./named-exports');
const substack = require('./substack');
const classExports = require('./class-exports');
const instanceExports = require('./instance-exports');


namedExports.info('This is named exports');

substack('This is substack');
substack.warn('This is substack');

const logger = new classExports('YJ-Logger');
logger.log('This is class exports');
logger.info('This is class exports');

instanceExports.log('This is instance');
instanceExports.log('This is instance');