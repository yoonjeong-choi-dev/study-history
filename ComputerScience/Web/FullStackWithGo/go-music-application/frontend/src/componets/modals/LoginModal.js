import React, { useState } from 'react';
import { Modal, ModalHeader, ModalBody } from 'reactstrap';


const SignInForm = (props) => {
  const [form, setForm] = useState({});
  const [error, setError] = useState('');

  const onChangeForm = (e) => {
    const elem = e.target;
    setForm({
      ...form,
      [elem.name]: elem.value
    });
  };

  const onClickToRegister = (e) => {
    e.preventDefault();
    props.setRegisterForm();
  };

  const onSubmitLogin = (e) => {
    e.preventDefault();
    alert(`Post Login : ${JSON.stringify(form)}`);

    // 로그인 상태로 변경
    props.setLoginState(form);
  }

  return (
    <div>
      {(error) ? <h5 className='mb-4 text-danger'>{error}</h5> : null}
      <form onSubmit={onSubmitLogin}>
        <h5 className='mb-4'>Basic Info</h5>

        <div className='form-group'>
          <label htmlFor='email'>Email:</label>
          <input name='email' type='email' className='form-control' id='email' onChange={onChangeForm} />
        </div>
        <div className='form-group'>
          <label htmlFor='password'>Password:</label>
          <input name='password' type='password' className='form-control' id='password' onChange={onChangeForm} />
        </div>

        <div className='form-row text-center'>
          <div className="col-12 mt-2">
            <button type="submit" className="btn btn-secondary btn-large">Sign In</button>
          </div>
          <div className="col-12 mt-2">
            <button type="submit" className="btn btn-link text-secondary" onClick={onClickToRegister}> New User? Register</button>
          </div>
        </div>
      </form>
    </div>
  )
};

const RegistrationForm = (props) => {
  const [form, setForm] = useState({});
  const [error, setError] = useState('');

  const onChangeForm = (e) => {
    const elem = e.target;
    setForm({
      ...form,
      [elem.name]: elem.value
    });
  };
  const onClickToSignIn = () => {
    props.setSignInForm();
  };

  const onSubmitRegister = (e) => {
    e.preventDefault();
    
    const {username, email, password1, password2} = form;
    if (!username || !email || !password1 || !password2) {
      setError('Please enter all form');
      return;
    }
    if (password1 !== password2) {
      setError('Passwords do not match');
      return;
    }

    alert(`Post Login : ${JSON.stringify(form)}`);
  }


  return (
    <div>
      {(error) ? <h5 className='mb-4 text-danger'>{error}</h5> : null}
      <form onSubmit={onSubmitRegister}>
        <h5 className='mb-4'>Registration</h5>

        <div className='form-group'>
          <label htmlFor='username'>User Name:</label>
          <input name='username' type='text' className='form-control' 
            id='username' onChange={onChangeForm} placeholder='Yoonjeon Choi' />
        </div>
        <div className='form-group'>
          <label htmlFor='email'>Email:</label>
          <input name='email' type='email' className='form-control' id='email' onChange={onChangeForm} />
        </div>
        <div className='form-group'>
          <label htmlFor='password2'>Password:</label>
          <input name='password1' type='password' className='form-control' id='password1' onChange={onChangeForm} />
        </div>
        <div className='form-group'>
          <label htmlFor='password2'>Confirm Password:</label>
          <input name='password2' type='password' className='form-control' id='password2' onChange={onChangeForm} />
        </div>

        <div className='form-row text-center'>
          <div className="col-12 mt-2">
            <button type="submit" className="btn btn-secondary btn-large">Register</button>
          </div>
          <div className="col-12 mt-2">
            <button type="submit" className="btn btn-link text-secondary" onClick={onClickToSignIn}> Sign In</button>
          </div>
        </div>
      </form>
    </div>
  )
}

export default function LoginModal(props) {
  const [register, setRegister] = useState(false);

  const registerUser = () => {
    setRegister(true);
  };

  const loginUser = () => {
    setRegister(false);
  }


  return (
    <Modal id="register" tabIndex="-1" role="dialog" isOpen={props.showModal} toggle={props.toggle}>
      <div role="document">
        <ModalHeader toggle={props.toggle} className="bg-secondary text-white">
          Sign in
        </ModalHeader>
        <ModalBody>
          {(register) ?
            <RegistrationForm setSignInForm={loginUser}/> :
            <SignInForm setRegisterForm={registerUser}  setLoginState={props.setLoginState} />
          }
        </ModalBody>
      </div>
    </Modal>
  )
}