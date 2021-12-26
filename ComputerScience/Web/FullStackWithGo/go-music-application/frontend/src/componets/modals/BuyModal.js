import React, { useState } from 'react';
import { Modal, ModalHeader, ModalBody } from 'reactstrap';
import {loadStripe} from '@stripe/stripe-js';
import {
  CardElement,
  Elements,
  useStripe,
  useElements,
} from '@stripe/react-stripe-js';


const stripePromise = loadStripe('pk_test_TYooMQauvdEDq54NiTphI7jx');

// 신용카드 결제 처리 과정에 대한 상태
const stripeStatus = {
  INITIAL: "INITIAL",
  SUCCESS: "COMPLETE",
  FAILED: "FAILED",
};

const CreditCardForm = (props) => {
  // 스트라이프 훅
  const stripe = useStripe();
  const elements = useElements();
  
  const [status, setStatus] = useState(stripeStatus.INITIAL);
  const [inputName, setInputName] = useState('');

  const onChangeCardName = (e) => {
    setInputName(e.target.value);
  };

  // 각 결제 처리 상태에 대한 렌더링 메서드 => 각 상태에 따라 다른 뷰 생성
  const renderCreditCardInfo = () => {
    // 스트라이프 컴포넌트에 적용할 스타일
    const style = {
      base: {
        'fontSize': '20px',
        'color': '#495057',
        'fontFamily': 'apple-system,BlinkMacSystemFont,"Segoe UI",Roboto,"Helvetica Neue",Arial,sans-serif'
      }
    };

    const userSavedCard = <div>
      <div className='form-row text-center'>
        <button type='button' className='btn btn-outline-success text-center mx-auto'>Use saved card?</button>
      </div>
      <hr />
    </div>;

    const rememberCardCheck = <div className='form-row form-check text-center'>
      <input className='form-check-input' type='checkbox' value="" id='remember-card-check' />
      <label className='form-check-label' htmlFor='remember-card-check'>
        Remember Card?
      </label>
    </div>;


    return (
      <div>
        {userSavedCard}
        <h5 className='mb-4'>Payment Info</h5>
        <form onSubmit={onSubmitPayment}>
          <div className='form-row'>
            <div className='col-lg-12 form-group'>
              <label htmlFor='cc-name'>Name On Card:</label>
              <input id='cc-name' name='cc-name' className='form-control' placeholder='Name on Card' onChange={onChangeCardName} type='text' />
            </div>
          </div>

          <div className='form-row'>
            <div className='col-lg-12 form-group'>
              <label htmlFor='card'>Card Information:</label>
              <CardElement id='card' className='form-control' style={style} />
            </div>
          </div>

          {rememberCardCheck}
          <hr className='mb-4' />
          <button type='submit' className='btn btn-success btn-large'>{props.operation}</button>
        </form>
      </div>
    )
  }

  const renderSuccess = () => {
    // 결제 성공 시 모달 토글 버튼 제공
    return (
      <div>
        <h5 className="mb-4 text-success">Credit card payment processed.....</h5>
        <button type="submit" className="btn btn-success btn-large" onClick={() => { props.toggle() }}>Ok</button>
      </div>
    );
  }

  const renderFailure = () => {
    // 실패 시, 실패 이유와 함께 결제 UI를 다시 렌더링
    return (
      <div>
        <h5 className="mb-4 text-danger"> Credit card information invalid, try again or exit</h5>
        {renderCreditCardInfo()}
      </div>
    );
  }

  // 결제 프로세스
  const onSubmitPayment = async (e) => {
    e.preventDefault();
    console.log('------------------------')
    
    // Stripe API를 통해 토큰 발급
    // 4242424242424242
    const cardElement = elements.getElement("card");
    const {token} = await stripe.createToken(cardElement, {name : inputName});

    if (!token) {
      console.log('Invalid Token', token);
      setStatus(stripeStatus.FAILED);
      
      return;
    }

    //토큰을 백엔드로 전달 : 우선은 무조건 성공
    fetch('/charge', {
      method: 'POST',
      headers: {'Content-Type': 'text/plain'},
      body: JSON.stringify({
        token: token.id,
        operation: props.operation,
      })
    }).then(res=> {
      console.log('Purchase Complete');
      setStatus(stripeStatus.SUCCESS);
    }).catch(err => {
      console.log('Server Error...');
      // 우선은 무조건 성공으로 한다
      setStatus(stripeStatus.SUCCESS);
    })
  };

  // 현재 결제 처리 상태에 대한 뷰 반환
  const renderStatus = () => {
    switch (status) {
      case stripeStatus.INITIAL:
        return renderCreditCardInfo();
      case stripeStatus.SUCCESS:
        return renderSuccess();
      case stripeStatus.FAILED:
        return renderFailure();
    }
  }

  return (
    <div>
      {renderStatus()}
    </div>
  )
}

const CreditCardPayment = (props) => {
  // 모달이 없는 경우 렌더링하지 않음
  if (!props.show) {
    return null;
  }

  // 스트라이프 API를 이용하여 CreditCardForm을 래핑한 컴포넌트 반환
  return (
    <div>
      <Elements stripe={stripePromise} >
          <CreditCardForm operation={props.operation} toggle={props.toggle}/>
      </Elements>
    </div>
  )
}

export default function BuyModal(props) {
  return (
    <Modal i='buy' tabIndex='-1' role='dialog' isOpen={props.showModal} toggle={props.toggle}>
      <div role='document'>
        <ModalHeader toggle={props.toggle} className='bg-success-text-white'>
          Buy Item
        </ModalHeader>
        <ModalBody>
          <CreditCardPayment show={true} productid={props.productid} price={props.price} operation="Charge" toggle={props.toggle} />
        </ModalBody>
      </div>
    </Modal>
  );
};