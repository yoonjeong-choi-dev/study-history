import React from 'react';

const Button = (props) => {
    return React.createElement(
        'button',
        { onClick: () => alert(props.label)},
        props.label
    );
};

export default Button;