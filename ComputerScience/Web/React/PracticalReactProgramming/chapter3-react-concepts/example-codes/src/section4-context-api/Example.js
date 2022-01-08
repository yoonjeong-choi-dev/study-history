import React, { useState } from 'react';
const UserContext = React.createContext('');

const Greet = () => {
  return (
    <UserContext.Consumer>
      {username => <p>{`Hello~ ${username}`}</p>}
    </UserContext.Consumer>
  )
};

// memo를 사용하여, 컨텍스트 변경 시 렌더링하지 않음
const Profile = React.memo(() => {
  return (
    <div>
      <Greet />
      <p>This is a Profile </p>
    </div>
  );
});

export default function Example() {
  const [username, setUsername] = useState('');

  const onChangeInput = (e) => {
    setUsername(e.target.value);
  };

  return (
    <div>
      <UserContext.Provider value={username}>
        <Profile />
      </UserContext.Provider>
      <input type='text' value={username} onChange={onChangeInput} />
    </div>
  );
}