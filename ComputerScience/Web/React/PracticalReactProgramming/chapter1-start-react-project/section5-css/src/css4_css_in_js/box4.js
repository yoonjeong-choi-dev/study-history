import React from "react";
import styled from 'styled-components';

// CSS 정의
const BoxCommon = styled.div`
  height: 50px;
  background-color: blue;
`;

const BoxBig = styled(BoxCommon)`
  width: 200px;
`;

const BoxSmall = styled(BoxCommon)`
  width: 100px;
`;

const BoxDynamic = styled.div`
  width: ${props => (props.isBig)? 200 : 100}px;
  height: 50px;
  background-color: blue;
`;

const Box4 = ({ size }) => {
  const isBig = size==='big';
  let divCotent = (isBig)? 'Big Box' : 'Small Box';

  return (
    <BoxDynamic isBig={isBig}>{divCotent}</BoxDynamic>
  );
};

export default Box4;