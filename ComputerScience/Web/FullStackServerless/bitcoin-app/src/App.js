import './App.css';
import React, {useState, useEffect} from 'react';
import { API } from "aws-amplify";

const bitcoinStyle = {
  border: "solid",
  padding: "10px",
  width: "300px"
}

const Bitcoin = ({name, symbol, price_usd, percent_change_24h, rank}) => {
  return (
    <div style={bitcoinStyle}>
            <h2>{name} - {symbol}</h2>
            <p> Rank : {rank} </p>
            <h5>Current Price : ${price_usd}</h5>
            <h5>Change Percnet(24h) : {percent_change_24h}%</h5>
    </div>
  )
}


const App = () => {
  // api 요청에 사용할 사용자 인풋
  const [input, updateInput] = useState({limit: 5, start: 0});

  const updateInputValue = (type, value) => {
    updateInput({...input, [type]: value })
  }

  // coins 정보 상태 초기화
  const [coins, updateCoins] = useState([]);

  // API 호출을 위한 fetch 함수 정의
  const fetchCoins = async () => {
    const {limit, start} = input;
    // coinapi : amplify add api를 통해 생성한 게이트웨이 주소
    const data = await API.get("coinapi", `/coins?limit=${limit}&start=${start}`);
    updateCoins(data.coins);
  }

  // 컴포넌트 마운트 시 fetch 진행
  useEffect(()=> {
    fetchCoins();
  }, []);

  return (
    <div className="App">
      <input onChange={ e=> updateInputValue("limit", e.target.value)}
        placeholder="limit"/>
      <input onChange= {e=>updateInputValue("start", e.target.value)}
        placeholder="start"/>
      <button onClick={fetchCoins}>Get Coin Data</button>
      {
        coins.map((coin,index) => (
          <Bitcoin key={index} {...coin} />
        ))
      }
    </div>
  );
}

export default App;
