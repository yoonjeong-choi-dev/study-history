import React from "react";
import './button1.css';

const Button1 = ({size}) => {
    let className = '';
    let buttonTitle = '';
    if (size === 'big') {
        className = 'button big';
        buttonTitle = 'Big Button';
    } else {
        className = 'button small';
        buttonTitle = 'Small Button';
    }

    return <button className={className}>{buttonTitle}</button>
};

export default Button1;