import React, { useState } from 'react';
import { BrowserRouter as Router, Routes, Route } from "react-router-dom";

import Navigation from './componets/Navigation';
import Home from './pages/Home';
import Promo from './pages/Promo'
import About from './pages/About';
import OrderInfo from './pages/OrderInfo';

import BuyModal from './componets/modals/BuyModal';
import LoginModal from './componets/modals/LoginModal';


const App = () => {
  const [user, setUser] = useState({loggedIn: false});
  const [buyModal, setBuyModal] = useState({ show: false });
  const [loginModal, setLoginModal] = useState({show:false});

  const login = (user) => {
    setUser({
      ...user,
      loggedIn: true,
    });

    // 로그인 모달 없애기
    setLoginModal({show: false});
  }

  const logout = () => {
    setUser({
      loggedIn: false,
    });
  }
  
  const showBuyModal = (id, price) => {
    setBuyModal({
      show: true,
      productid: id,
      price: price
    });
  };

  const toggleBuyModal = () => {
    setBuyModal({...buyModal, show: !buyModal.show});
  };

  const showLoginModal = (id, price) => {
    setLoginModal({
      show: true
    });
  };

  const toggleLoginModal = () => {
    setLoginModal({show: !loginModal.show});
  };

  return (
    <div>
      <Router>
        <div>
          <Navigation user={user} setLogoutState={logout} showLoginModal={showLoginModal}/>
          <div className='container pt-4 mt-4'>
            <Routes>
              <Route exact path="/" element={<Home showBuyModal={showBuyModal}/>} />
              <Route exact path="/promos" element={<Promo showBuyModal={showBuyModal}/>} />
              {user.loggedIn ? <Route exact path="/myorders" element={<OrderInfo />}/> : null}
              <Route exact path="/about" element={<About />} />
              <Route path="*" element={<Home />} />
            </Routes>
          </div>
          <LoginModal setLoginState={login} showModal={loginModal.show} toggle={toggleLoginModal}/>
          <BuyModal showModal={buyModal.show} toggle={toggleBuyModal}
            productid={buyModal.productid} price={buyModal.price}/>
        </div>
      </Router>
    </div>
  )
};

export default App;