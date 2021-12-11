const LikeButton = () => {
    const [liked, setLiked] = React.useState(false);

    const text = liked ? '좋아요 취소' : '좋아요';
    return React.createElement(
        'div',
        null,
        React.createElement(
            'button',
            {
                onClick: () => setLiked(!liked),
                style: {margin : '20px 0 20px 0'},
            },
            text,
        ),
    );
};

const Container = () => {
    const [count, setCount] = React.useState(0);

    return React.createElement(
        'div',
        null,
        React.createElement(LikeButton),
        React.createElement(
            'div',
            {style: {margin : '20px 0 20px 0'},},
            React.createElement('span', null, 'Count : '),
            React.createElement('span', null, count),
            React.createElement(
                'div',
                null,
                React.createElement(
                    'button',
                    { onClick: () => setCount(count+1)},
                    '+',
                ),
                React.createElement(
                    'button',
                    { onClick: () => setCount(count-1)},
                    '-',
                )
            )
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