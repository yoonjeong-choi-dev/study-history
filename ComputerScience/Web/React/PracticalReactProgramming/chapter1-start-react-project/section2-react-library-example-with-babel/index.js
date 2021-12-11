const LikeButton = () => {
  const [liked, setLiked] = React.useState(false);
  const text = liked ? '좋아요 취소' : '좋아요';
  return /*#__PURE__*/React.createElement("div", null, /*#__PURE__*/React.createElement("button", {
    onClick: () => setLiked(!liked),
    style: {
      margin: '20px 0 20px 0'
    }
  }, text));
};

const Container = () => {
  const [count, setCount] = React.useState(0);
  return /*#__PURE__*/React.createElement("div", {
    style: {
      margin: '20px 0 20px 0'
    }
  }, /*#__PURE__*/React.createElement(LikeButton, null), /*#__PURE__*/React.createElement("span", null, "Count : ", count), /*#__PURE__*/React.createElement("div", null, /*#__PURE__*/React.createElement("button", {
    onClick: () => setCount(count + 1)
  }, "+"), /*#__PURE__*/React.createElement("button", {
    onClick: () => setCount(count - 1)
  }, "-+")));
};

const Root = () => {
  return /*#__PURE__*/React.createElement("div", null, /*#__PURE__*/React.createElement("div", null, "\uC5EC\uAE30\uB294 \uB9AC\uC561\uD2B8\uC5D0\uC11C \uAD00\uB9AC\uD558\uB294 \uB3D4\uC785\uB2C8\uB2E4"), /*#__PURE__*/React.createElement(Container, null));
}; // cra(create-react-app)에서 index.js의 마지막에 있는 구문


const domContainer = document.querySelector('#react-root');
ReactDOM.render(React.createElement(Root), domContainer);