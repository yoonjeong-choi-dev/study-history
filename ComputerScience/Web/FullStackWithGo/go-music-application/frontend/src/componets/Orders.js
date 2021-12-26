import React, { useState, useEffect } from 'react';

const Order = (props) => {
  return (
    <div className="col-12">
      <div className="card text-center">
        <div className="card-header"><h5>{props.productname}</h5></div>
        <div className="card-body">
          <div className="row">
            <div className="mx-auto col-6">
              <img src={props.img} alt={props.imgalt} className="img-thumbnail float-left" />
            </div>
            <div className="col-6">
              <p className="card-text">{props.desc}</p>
              <div className="mt-4">
                Price: <strong>{props.price}</strong>
              </div>
            </div>
          </div>
        </div>
        <div className="card-footer text-muted">
          Purchased {props.days} days ago
        </div>
      </div>
      <div className="mt-3" />
    </div>
  );
};

export default function OrderContainer(props) {
  const [orders, setOrders] = useState([]);

  useEffect(()=> {
    console.log('Fetch the user data');

    // npm start로 실행 시, 웹서버 구동 => public 내의 정적 리소스 접근 가능
    fetch(props.location)
      .then(res => res.json())
      .then(data => {
        setOrders(data.orders);
      })
      .catch(err => console.error('Cannot fetch the user data'));
  },[]);

  return (
    <div className='row mt-5'>
      {orders.map(order => <Order key={order.id} {...order} />)}
    </div>
  )
};