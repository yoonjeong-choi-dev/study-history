import React from 'react';
import CardContainer from '../componets/ProductsCard';

export default function Home(props) {
  return (
    <div className='container pt-4'>
      <CardContainer location='cards.json' showBuyModal={props.showBuyModal}/>
    </div>
  )
};