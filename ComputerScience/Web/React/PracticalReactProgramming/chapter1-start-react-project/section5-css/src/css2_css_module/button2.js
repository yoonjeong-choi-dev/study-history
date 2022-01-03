import React from "react";
import style from './button2.module.css';

const Button2 = ({size}) => {
    let divCotent = (size === 'big')? 'Big Button' : 'Small Button';

  if (size === 'big') {
    return <button className={`${style.button} ${style.big}`}>{divCotent}</button>
  } else {
    return <button className={`${style.button} ${style.small}`}>{divCotent}</button>
  }
};

console.log('button style', style);
export default Button2;