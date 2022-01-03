import React from 'react';
import Container from '../container';

import Button1 from './button1';
import Box1 from './box1';

// 일반적인 CSS 파일을 임포트하는 방식
export default function Example1() {
  return (
    <Container title='General CSS'>
        <Button1 size='big'/>
        <Button1 size='small' />
        <Box1 size='big'/>
        <Box1 size='small'/>
      </Container>
  );
};