import { addNumber } from './utils';

it('add two numbers', ()=> {
    const result = addNumber(1,3);
    expect(result).toBe(4);
});