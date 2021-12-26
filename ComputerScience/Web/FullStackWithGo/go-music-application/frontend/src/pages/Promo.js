import React from 'react';
import CardContainer from '../componets/ProductsCard';

export default function Promo(props) {
  return (
    <CardContainer location='promos.json' promo={true} showBuyModal={props.showBuyModal}/>
  )
};