import React, { useState, useEffect } from 'react';
import ReactDOM from 'react-dom';

const Card = ({ img, imgAlt, desc, price, productname }) => {
  return (
    <div className="col-md-6 col-lg-4 d-flex align-items-stretch">
      <div className="card mb-3">
        <img className="card-img-top" src={img} alt={imgAlt} />
        <div className="card-body">
          <h4 className="card-title">{productname}</h4>
          Price: {price}
          <p className="card-text">{desc}</p>
          <a className="btn btn-success text-white" >
            Buy
          </a>
        </div>
      </div>
    </div>
  );
};

const CardContainer = () => {
  const [cards, setCards] = useState([]);

  useEffect(()=> {
    console.log('Fetch the cards data');

    // npm start로 실행 시, 웹서버 구동 => public 내의 정적 리소스 접근 가능
    fetch('cards.json')
      .then(res => res.json())
      .then(data => {
        setCards(data);
      })
      .catch(err => console.error('Cannot fetch the cards data'));
  },[]);

  return (
    <div>
      <div className='container pt-4'>
        <h3 className='text-center text-primary'>Products</h3>
        <div className='pt-4 row'>
          { cards.map(card => <Card key={card.id} {...card} />) }
        </div>
      </div>
    </div>
  )
}

const Card1 = () => {
  const img = 'img/strings.png';
  const imgAlt = 'string';
  const desc = 'A very authentic and beatiful instrument!';
  const price = 100;
  const name = 'Strings';

  return (
    <div className="col-md-6 col-lg-4 d-flex align-items-stretch">
      <div className="card mb-3">
        <img className="card-img-top" src={img} alt={imgAlt} />
        <div className="card-body">
          <h4 className="card-title">{name}</h4>
          Price: {price}
          <p className="card-text">{desc}</p>
          <a className="btn btn-success text-white" >
            Buy
          </a>
        </div>
      </div>
    </div>
  );
}

ReactDOM.render(
  <React.StrictMode>
    < CardContainer />
  </React.StrictMode>,
  document.getElementById('root')
);