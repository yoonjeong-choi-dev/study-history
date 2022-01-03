import React from "react";
import cn from 'classnames';
import style from './button3.module.scss';

const Button2 = ({size}) => {
  const isBig = size==='big';
  let divCotent = (isBig)? 'Big Button' : 'Small Button';

  return (
    <button 
      className={cn(style.button, { [style.big]: isBig, [style.small]: !isBig})}
    >
      {divCotent}
    </button>
  );
};

console.log('button style', style);
export default Button2;