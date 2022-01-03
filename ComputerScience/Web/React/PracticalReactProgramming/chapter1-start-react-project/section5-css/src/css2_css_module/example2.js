import React from 'react';
import Container from '../container';

import Button2 from './button2';
import Box2 from './box2';

// {컴포넌트}.module.css 파일을 임포트하는 방식
export default function Example2() {
  return (
    <Container title='General CSS'>
        <Button2 size='big'/>
        <Button2 size='small' />
        <Box2 size='big'/>
        <Box2 size='small'/>
      </Container>
  );
};