import React from 'react';
import { BrowserRouter, Routes, Route, Link } from 'react-router-dom';
import Rooms, {Room} from './Room';

const Home = ({ match }) => {
  return <h2>이곳은 홈페이지입니다</h2>;
};

const Photo = ({ match }) => {
  return <h2>여기서 사진을 감상하세요</h2>;
};

export default function ReactRouterDom() {
  return (
    <BrowserRouter>
      <div style={{ marginBottom: '10px', padding: '10px', border: '2px solid black' }}>
        <h1>React Router DOM Example</h1>
        <div>
          <Link to='/'>Home</Link>
          <br />
          <Link to='/photo'>Photo</Link>
          <br />
          <Link to='/rooms'>Rooms</Link>
          <br />
          <Routes>
            <Route exact path='/' element={<Home />} />
            <Route path='/photo' element={<Photo />} />
            <Route path='/rooms' element={<Rooms />}>
              <Route path=':roomId' element={<Room/>}/>
            </Route>
          </Routes>
        </div>
      </div>
    </BrowserRouter>
  );
};