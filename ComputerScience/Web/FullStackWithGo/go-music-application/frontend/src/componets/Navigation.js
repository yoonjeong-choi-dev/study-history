import React from 'react';
import { Link, useNavigate } from 'react-router-dom';

const Navigation = (props) => {
  const navigate = useNavigate();

  const onClickLogout = (e) => {
    props.setLogoutState();
    navigate('/');
  }

  // 로그인시 활성화되는 메뉴
  const buildLoggedInMenu = () => {
    return (
      <div className='navbar-brand order-1 text-white my-auto'>
        <div className='btn-group'>
          <button type='button' className='btn btn-secondary dropdown-toggle' 
            data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
            Welcome {props.user.name}
          </button>
          <div className='dropdown-menu'>
            <button className='btn dropdown-item' onClick={onClickLogout}>Sign Out</button>
          </div>
        </div>
      </div>
    );
  }

  const showModalWindow = () => {
    props.showLoginModal();
  };

  return (
    <nav className='navbar navbar-expand-sm navbar-dark bg-secondary'>
      <div className='container'>
        {
          props.user.loggedIn ?
            buildLoggedInMenu() :
            <button type='button' className='navbar-brand order-1 btn btn-secondary'
              onClick={showModalWindow}>Sign in</button>
        }
        <div className='navbar-collapse' id='navbarNavAltMarkup'>
          <div className='navbar-nav'>
            <Link className='nav-item nav-link' to='/'>Home</Link>
            <Link className='nav-item nav-link' to='/promos'>Promotions</Link>
            {props.user.loggedIn ? <Link className="nav-item nav-link" to="/myorders">My Orders</Link> : null}
            <Link className='nav-item nav-link' to='/about'>About</Link>
          </div>
        </div>
      </div>
    </nav>
  )
};

export default Navigation;