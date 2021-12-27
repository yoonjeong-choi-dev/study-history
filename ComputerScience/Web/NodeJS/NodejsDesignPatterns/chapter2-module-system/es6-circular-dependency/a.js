import * as bModule from './b.js';

console.log('a : export loaded...');
export let loaded = false;

console.log('a : export b...');
export const b = bModule;

console.log('a : loaded=true');
loaded = true;