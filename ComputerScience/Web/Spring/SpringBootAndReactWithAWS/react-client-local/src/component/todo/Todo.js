import React, { useState } from "react";
import { ListItem, ListItemText, ListItemSecondaryAction, InputBase, Checkbox, IconButton } from "@material-ui/core";
import { DeleteOutlined } from "@material-ui/icons";

const Todo = (props) => {
  const [state, setState] = useState({ item: props.item, readOnly: true });

  const onClickCheckbox = (e) => {
    const thisItem = state.item;
    thisItem.done = !thisItem.done;
    setState({ item: thisItem });
    props.update(state.item);
  };

  const onClickDelete = () => {
    props.delete(state.item);
  };

  const onClickForEditMode = () => {
    setState(
      {
        ...state,
        readOnly: false
      }
    );
  };

  const onPressKeyEnter = (e) => {
    if (e.key === 'Enter') {
      setState({
        ...state,
        readOnly: true,
      });

      props.update(state.item);
    }
  };

  const onEditInput = (e) => {
    const item = state.item;
    item.title = e.target.value;

    setState({
      ...state,
      item
    })
  }

  const item = state.item;
  return (
    <ListItem>
      <Checkbox checked={item.done} onChange={onClickCheckbox} />

      <ListItemText>
        <InputBase
          inputProps={{
            "aria-label": "naked",
            readOnly: state.readOnly,
          }}
          type='text'
          id={item.id}
          name={item.name}
          value={item.title}
          multiline={true}
          fullWidth={true}
          onClick={onClickForEditMode}
          onKeyPress={onPressKeyEnter}
          onChange={onEditInput}
        />
      </ListItemText>

      <ListItemSecondaryAction>
        <IconButton aria-label="Delete Todo" onClick={onClickDelete}>
          <DeleteOutlined />
        </IconButton>
      </ListItemSecondaryAction>

    </ListItem>
  );

};

export default Todo;