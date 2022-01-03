import React from "react";
import './box1.css'

const Box1 = ({ size }) => {
  let className = '';
  let divCotent = '';
  if (size === 'big') {
    className = 'box big';
    divCotent = 'Big Box';
  } else {
    className = 'box small';
    divCotent = 'Small Box';
  }

  return <div className={className}>{divCotent}</div>
};

export default Box1;