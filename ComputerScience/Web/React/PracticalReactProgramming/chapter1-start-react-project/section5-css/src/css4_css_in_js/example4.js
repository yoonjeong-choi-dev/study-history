import React from 'react';
import Container from '../container';

import Button4 from './button4';
import Box4 from './box4';

// {컴포넌트}.module.css 파일을 임포트하는 방식
export default function Example4() {
  return (
    <Container title='General CSS'>
        <Button4 size='big'/>
        <Button4 size='small' />
        <Box4 size='big'/>
        <Box4 size='small'/>
      </Container>
  );
};