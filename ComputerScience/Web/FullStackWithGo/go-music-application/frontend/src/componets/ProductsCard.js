import React, { useState, useEffect } from 'react';

const Card = (props) => {
  const priceColor = (props.promo)? 'text-danger' : 'text-dark';

  const onClickBuy = (e) => {
    props.showBuyModal(props.id, props.price)
    //alert(`Buy the item ${props.id} with \$${props.price}`);
  };

  return (
    <div className="col-md-6 col-lg-4 d-flex align-items-stretch">
      <div className="card mb-3">
        <img className="card-img-top" src={props.img} alt={props.imgAlt} />
        <div className="card-body">
          <h4 className="card-title">{props.productname}</h4>
          Price: <strong className={priceColor}>{props.price}</strong>
          <p className="card-text">{props.desc}</p>
          <a className="btn btn-success text-white" onClick={onClickBuy}>
            Buy
          </a>
        </div>
      </div>
    </div>
  );
};

const CardContainer = (props) => {
  const [cards, setCards] = useState([]);

  useEffect(() => {
    console.log('Fetch the cards data');

    // npm start로 실행 시, 웹서버 구동 => public 내의 정적 리소스 접근 가능
    fetch(props.location)
      .then(res => res.json())
      .then(data => {
        setCards(data);
      })
      .catch(err => console.error('Cannot fetch the cards data'));
  }, []);

  return (
    <div className='mt-5 row'>
      {cards.map(card => 
        <Card key={card.id} {...card} promo={props.promo} showBuyModal={props.showBuyModal}/>
      )}
    </div>
  );
};

export default CardContainer;