import React from "react";
import cn from 'classnames';
import style from './box3.module.scss';

const Box2 = ({ size }) => {
  const isBig = size==='big';
  let divCotent = (isBig)? 'Big Box' : 'Small Box';

  return (
    <div 
      className={cn(style.box, { [style.big]: isBig, [style.small]: !isBig})}
    >
      {divCotent}
    </div>
  );
};

console.log('box style', style);
export default Box2;