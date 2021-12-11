import './App.css';
import TodoList from './code_splitting/TodoList';
import smallImage from './smallImg.svg'
import bigImage from './big.jpeg'

function App() {
  // 현재 개발 환경 출력
  console.log(`NODE_ENV : ${process.env.NODE_ENV}`);
  console.log(process.env);
  // 현재 개발 환경에 대해 설정한 환경 변수 
  console.log(`REACT_APP_DATA_API : ${process.env.REACT_APP_DATA_API}`);
  console.log(`REACT_APP_LOGIN_API : ${process.env.REACT_APP_LOGIN_API}`);

  return (
    <div className="App">
      <header className="App-header">
        <h1>This is the first React App with CRA</h1>
        <img src={bigImage} alt="big" style={{ width: '10%' }} />
        <img src={smallImage} alt="small" style={{ width: '10%' }} />
      </header>
      <TodoList/>
    </div>
  );
}

export default App;
