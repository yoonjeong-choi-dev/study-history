import React, { useState, useEffect } from 'react';
import { Paper, List, Container, Grid, Button, AppBar, Toolbar, Typography } from '@material-ui/core';

import Todo from '../component/todo/Todo';
import TodoCreate from '../component/todo/TodoCreate';
import { callAPI, signout } from '../shared/APIService';


const TodoPage = () => {
  const [state, setState] = useState(
    {
      items: [],
      loading: true,
    }
  );

  useEffect(() => {
    callAPI('/todo', 'GET', null)
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

  let navigationBar = (
    <AppBar position='static'>
      <Toolbar>
        <Grid justifyContent='space-between' container>
          <Grid item>
            <Typography variant='h6'>Todo App!</Typography>
          </Grid>

          <Grid>
            <Button color='inherit' onClick={signout}>
              로그아웃
            </Button>
          </Grid>

        </Grid>
      </Toolbar>
    </AppBar>
  );

  let todoPage = (
    <div>
      {navigationBar}
      <Container maxWidth='md'>
        <TodoCreate add={addTodo} />
        <div className='TodoList'>{todoItems}</div>
      </Container>
    </div>
  );

  let loadingPage = <h1>Loading...</h1>;

  let content = loadingPage;
  if(!state.loading) content = todoPage;

  return (
    <div style={{ paddingTop: 40, textAlign: 'center' }}>
      {content}
    </div>
  );
}

export default TodoPage;
