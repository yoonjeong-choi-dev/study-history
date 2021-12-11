import React from "react";
import ReactDOM from "react-dom";
import Button from './Button.js';

const Container = () => {
    return React.createElement(
        'div',
        null,
        React.createElement(
            'div',
            {style: {margin : '20px 0 20px 0'},},
            React.createElement('p', null, '버튼을 클릭하세요'),
            React.createElement(Button, {label: '좋아요'}),
            React.createElement(Button, {label: '싫어요'})
        )
    )
};

const Root = () => {
    return React.createElement(
        'div',
        null,
        '여기는 리액트에서 관리하는 돔입니다',
        React.createElement(Container),
    );
};

// cra(create-react-app)에서 index.js의 마지막에 있는 구문
const domContainer = document.querySelector('#react-root');
ReactDOM.render(React.createElement(Root), domContainer);