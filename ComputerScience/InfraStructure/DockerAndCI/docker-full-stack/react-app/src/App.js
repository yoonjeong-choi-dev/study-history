import React, { useState, useEffect } from 'react';
import './App.css';

import axios from 'axios';

const App = () => {
  // input 태그의 value 상태 관리
  const [value, setValue] = useState("");

  // DB에 저장되어 있는 메시지 리스트 상태 관리
  const [lists, setLists] = useState([]);

  // 마운트 시, 서버에서 데이터 fetch
  useEffect(() => {
    axios.get('/api/values')
      .then(res => {
        console.log('response', res);
        const list = res.data.map(d => d.value);
        setLists(list);
      })
      .catch(err => {
        console.error('Cannot fetch the data', err);
      });
  }, []);

  // input form 관리
  const onChangeInput = (e) => {
    setValue(e.target.value);
  };

  // form submit 이벤트
  const onSubmitForm = (e) => {
    // form default action 무시
    e.preventDefault();

    // 서버로 메시지 Post
    axios.post('/api/value', { value: value })
      .then(res => {
        // 성공한 경우 : 리스트 상태 업데이트
        if (res.data.success) {
          console.log('response', res);
          setLists([...lists, res.data.value]);

          // Reset the form
          setValue("");
        } else {
          alert('Fail to insert data into DB');
        }
      })
      .catch(err => {
        console.error('Cannot post the data', err);
      })
  }

  return (
    <div className="App">
      <header className="App-header">
        <h3>Hello! This is YJ App with Docker Containers!</h3>
        <h4>This is a simple full-stack app</h4>
        <a
          className="App-link"
          href="https://github.com/yoonjeong-choi-dev"
          target="_blank"
          rel="noopener noreferrer"
        >
          Visit YJ Github!
        </a>

        <div className="container">
          {lists && lists.map((list, id) => {
            return <li key={id}>{list}</li>
          })}

          <form className="example" onSubmit={onSubmitForm}>
            <input type="text"
              placeholder="입력해주세요..."
              onChange={onChangeInput}
              value={value}
            />
            <button type="submit">확인</button>
          </form>
        </div>


      </header>
    </div>
  );
};

export default App;
