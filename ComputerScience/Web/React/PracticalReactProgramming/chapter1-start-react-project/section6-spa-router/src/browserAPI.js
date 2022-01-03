import React, { useEffect } from 'react';

export default function BrowserAPI() {
  useEffect(() => {
    window.onpopstate = (e) => {
      console.log(`location : ${document.location}, state: ${e.state}`);
    };
  }, []);

  const onClickPage1 = () => {
    window.history.pushState('v1', '', '/page1');
  };

  const onClickPage2 = () => {
    window.history.pushState('v2', '', '/page2');
  };

  return (
    <div style={{ marginBottom: '10px', padding: '10px', border: '2px solid black' }}>
      <h1>BrowserAPI Example</h1>
      <div>
        <button onClick={onClickPage1}>page1</button>
        <button onClick={onClickPage2}>page2</button>
      </div>
    </div>
  );
};