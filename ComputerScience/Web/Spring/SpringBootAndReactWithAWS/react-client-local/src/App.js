import React, { useState, useEffect } from 'react';
import { callAPI } from './shared/APIService';
import Todo from './component/Todo';
import TodoCreate from './component/TodoCreate';
import { Paper, List, Container, Typography } from '@material-ui/core';

const App = () => {
  const [state, setState] = useState(
    {
      items: [],
      loading: true,
    }
  );

  // useEffect(() => {
  //   fetch('http://localhost:2205/todo/all', {
  //     method: 'GET',
  //     headers: {
  //       'Content-Type': 'application/json'
  //     }
  //   })
  //     .then(res => res.json())
  //     .then(res => {
  //       setState({
  //         items: res.data,
  //         loading: false,
  //       })
  //     })
  //     .catch(err => {
  //       console.error(err);
  //       setState({
  //         items: [],
  //         loading: true,
  //         error: err
  //       });
  //     });
  // }, []);

  useEffect(() => {
    callAPI('/todo/all', 'GET', null)
      .then((res) =>
        setState({ items: res.data, loading: false })
      );
  }, []);

  const addTodo = (item) => {
    callAPI('/todo', 'POST', item)
      .then((res) =>
        setState({ ...state, items: res.data })
      );
  };

  const deleteTodo = (item) => {
    callAPI('/todo', 'DELETE', item)
      .then((res) =>
        setState({ ...state, items: res.data })
      );
  };

  const updateTodo = (item) => {
    callAPI('/todo', 'PUT', item)
      .then((res) =>
        setState({ ...state, items: res.data })
      );
  };

  let todoItems = state.items.length > 0 && (
    <Paper style={{ margin: 16 }}>
      <List>
        {state.items.map((item) => {
          return <Todo
            item={item} key={item.id}
            delete={deleteTodo}
            update={updateTodo}
          />;
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
