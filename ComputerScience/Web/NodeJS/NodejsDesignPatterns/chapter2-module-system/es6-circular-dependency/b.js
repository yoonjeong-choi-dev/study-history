import * as aModule from './a.js';

console.log('b : export loaded...');
export let loaded = false;

console.log('b : export a...');
export const a = aModule;

console.log('b : loaded=true');
loaded = true;