import React, { useState } from "react";
import { TextField, Paper, Button, Grid } from "@material-ui/core";

const TodoCreate = (props) => {
  const [state, setState] = useState({ item: { title: "" } });

  const onAddButtonClick = () => {
    props.add(state.item);
    setState({ item: { title: "" } });
  };

  const onInputChange = (e) => {
    const curItem = state.item;
    curItem.title = e.target.value;
    setState({ item: curItem });
    //console.log("Changed input : " + JSON.stringify(curItem));
  };

  const onPressKeyEnter = (e) => {
    if(e.key === 'Enter') {
      onAddButtonClick();
    }
  };

  

  return (
    <Paper style={{ margin: 16, padding: 16 }}>
      <Grid container>
        <Grid xs={11} md={11} item style={{ paddingRight: 16 }}>
          <TextField
            placeholder='Create Todo Here'
            fullWidth
            onChange={onInputChange}
            onKeyPress={onPressKeyEnter}
            value={state.item.title}
          />
        </Grid>

        <Grid xs={1} md={1} item>
          <Button fullWidth color='secondary' variant="outlined" onClick={onAddButtonClick}>
            +
          </Button>
        </Grid>

      </Grid>
    </Paper>
  )
};

export default TodoCreate;