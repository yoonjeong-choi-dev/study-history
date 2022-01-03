import React from 'react';
import Container from '../container';

import Button3 from './button3';
import Box3 from './box3';

// {컴포넌트}.module.css 파일을 임포트하는 방식
export default function Example3() {
  return (
    <Container title='General CSS'>
        <Button3 size='big'/>
        <Button3 size='small' />
        <Box3 size='big'/>
        <Box3 size='small'/>
      </Container>
  );
};