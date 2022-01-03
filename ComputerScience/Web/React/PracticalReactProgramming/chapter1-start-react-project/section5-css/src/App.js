import Example1 from './css1_general_css/example1';
import Example2 from './css2_css_module/example2';
import Example3 from './css3_sass/example3';
import Example4 from './css4_css_in_js/example4';

function App() {
  return (
    <div>
      <h1>This is an example for general CSS style </h1>
      <Example1 />
      <h1>This is an example for CSS-module</h1>
      <Example2 />
      <h1>This is an example for SASS</h1>
      <Example3 />
      <h1>This is an example for css-in-js</h1>
      <Example4 />
    </div>
  );
}

export default App;
