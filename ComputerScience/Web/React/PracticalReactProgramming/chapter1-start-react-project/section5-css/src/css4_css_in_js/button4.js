import React from "react";
import styled from "styled-components";

// CSS 정의
const ButtonCommon = styled.button`
  height: 30px;
  background-color: red;
`;

const ButtonBig = styled(ButtonCommon)`
  width: 100px;
`;

const ButtonSmall = styled(ButtonCommon)`
  width: 50px;
`;

const Button4 = ({ size }) => {
  if (size === 'big') {
    return <ButtonBig>Big Button</ButtonBig>;
  } else {
    return <ButtonSmall>Small Button</ButtonSmall>;
  }
};

export default Button4;