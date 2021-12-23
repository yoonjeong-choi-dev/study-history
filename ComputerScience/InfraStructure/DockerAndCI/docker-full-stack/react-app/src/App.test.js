import { render, screen } from '@testing-library/react';
import App from './App';

test('renders <h1> tag for main title', () => {
  render(<App />);
  
  // 테스트 코드
  const linkElement = screen.getByText(/Hello! This is YJ React App with Docker Container!/i);
  expect(linkElement).toBeInTheDocument();
});

test('renders <h2> tag for description', () => {
  render(<App />);
  
  // 테스트 코드
  const linkElement = screen.getByText(/This is a simple app for docker test/i);
  expect(linkElement).toBeInTheDocument();
});

test('renders my github link', () => {
  render(<App />);
  
  // 테스트 코드
  const linkElement = screen.getByText(/Visit YJ Github!/i);
  expect(linkElement).toBeInTheDocument();
});
