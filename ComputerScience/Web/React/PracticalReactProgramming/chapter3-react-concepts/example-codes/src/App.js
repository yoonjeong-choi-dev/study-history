import Container from './container';
import Example1 from './section1-ui-data/Example';
import User from './section3-custom-hook/User';
import Example2 from './section4-context-api/Example';

function App() {
  return (
    <>
      <Container>
        <h1> UI Data </h1>
        <Example1 />
      </Container>
      <Container>
        <h1> Custom Hook </h1>
        <User userId='1' />
      </Container>
      <Container>
        <h1> Context API </h1>
        <Example2 />
      </Container>
    </>
  );
}

export default App;
