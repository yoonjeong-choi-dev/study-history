import { useState } from 'react';
import Todo from './component/Todo';
import TodoCreate from './component/TodoCreate';
import { Paper, List, Container, Typography } from '@material-ui/core';

const App = () => {
  const [state, setState] = useState(
    {
      items: [
        { id: '0', title: 'Todo Test 1', done: true },
        { id: '1', title: 'Todo Test 2', done: false },
      ]
    }
  );

  const addTodo = (item) => {
    const items = state.items;
    item.id = 'ID-' + items.length;
    item.done = false;
    items.push(item);
    setState({ items: items });
  };

  const deleteTodo = (item) => {
    const items = state.items;
    const itemsAfterDelete = items.filter(i => i.id !== item.id);
    setState({ items: itemsAfterDelete });
  };

  let todoItems = state.items.length > 0 && (
    <Paper style={{ margin: 16 }}>
      <List>
        {state.items.map((item) => {
          return <Todo item={item} key={item.id} delete={deleteTodo} />;
        })}
      </List>
    </Paper>
  );


  return (
    <div style={{ paddingTop: 40 }}>
      <Container>
        <Typography variant="h3">Todo App Local Client</Typography>
        <TodoCreate add={addTodo} />
        <div className='TodoList'>{todoItems}</div>
      </Container>
    </div>
  );
}

export default App;
