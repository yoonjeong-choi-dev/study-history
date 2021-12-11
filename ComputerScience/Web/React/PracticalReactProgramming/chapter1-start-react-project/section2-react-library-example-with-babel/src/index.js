const LikeButton = () => {
    const [liked, setLiked] = React.useState(false);

    const text = liked ? '좋아요 취소' : '좋아요';
    return (
        <div>
            <button onClick= {() => setLiked(!liked)} style={{margin : '20px 0 20px 0'}}>
                {text}
            </button>
        </div>
    );
};

const Container = () => {
    const [count, setCount] = React.useState(0);

    return (
        <div style= {{margin : '20px 0 20px 0'}}>
            <LikeButton/>
            <span>Count : {count}</span>
            <div>
                <button onClick={()=> setCount(count+1)}>+</button>
                <button onClick={()=> setCount(count-1)}>-+</button>
            </div>
        </div>
    );
};

const Root = () => {
    return (
        <div>
            <div>
                여기는 리액트에서 관리하는 돔입니다
            </div>
            <Container/>
        </div>
    );
};

// cra(create-react-app)에서 index.js의 마지막에 있는 구문
const domContainer = document.querySelector('#react-root');
ReactDOM.render(React.createElement(Root), domContainer);