import React from 'react';
import { Link, useParams, Outlet } from 'react-router-dom';

export const Room = ({ match }) => {
  const {roomId} = useParams();
  return <h2>{`${roomId} 방을 선택하셨습니다`}</h2>;
};

const Rooms = () => {
  return (
    <div>
      <h2>여기는 방을 소개하는 페이지입니다</h2>
      <Link to='./blueRoom'>파란 방입니다</Link>
      <br />
      <Link to='./redRoom'>빨간 방입니다</Link>
      <br />
      <Outlet/>
    </div>
  );
}


export default Rooms;
