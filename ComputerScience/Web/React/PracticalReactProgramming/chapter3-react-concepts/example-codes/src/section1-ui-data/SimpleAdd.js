import React, {useState} from 'react';

const SimpleAdd = React.memo((props) => {
  const [num, setNum] = useState(0);

  const onClick = (e) => {
    //num = num + 1;
    setNum(num+1);
  };

  return (
    <div style={{border: '2px solid red'}}>
      <h1>{props.title}</h1>
      <div>
        <h2>Current Number : {num}</h2>
        <button onClick={onClick}>Add</button>
      </div>
    </div>
  );
});

export default SimpleAdd;
//export default React.memo(SimpleAdd);