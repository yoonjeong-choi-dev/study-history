import './App.css';
import React, { useEffect, useReducer } from 'react';
import { API } from "aws-amplify";
import { List, Input, Button } from "antd";
import "antd/dist/antd.css";
import { listNotes } from "./graphql/queries";
import { 
  createNote as CreateNote,
  deleteNote as DeleteNote,
  updateNote as UpdateNote
} from "./graphql/mutations";
import { onCreateNote } from './graphql/subscriptions';
import { v4 as uuid } from "uuid";

// Define client id for subscription
const CLIENT_ID = uuid();


// Define initial state for reducer hook
const initialState = {
  notes: [],
  loading: true,
  error: false,
  form: {
    name: "",
    description: ""
  }
};

// Define redure for reduce hook
const reducer = (state, action) => {
  switch (action.type) {
    case "SET_NOTES":
      return {
        ...state,
        notes: action.notes,
        loading: false
      };
    case "ADD_NOTE":
      return {
        ...state,
        notes: [action.note, ...state.notes]
      };
    case "RESET_FORM":
      return {
        ...state,
        form: initialState.form
      };
    case "SET_INPUT":
      return {
        ...state,
        form: {
          ...state.form,
          [action.name]: action.value
        }
      };
    case "ERROR":
      return {
        ...state,
        loading: false,
        error: true
      };
    default:
      return state;
  }
}

const styles = {
  container: { padding: 20 },
  input: { marginBottom: 10 },
  item: { textAlight: "left" },
  p: { color: "#1890ff" }
};

const App = () => {
  const [state, dispatch] = useReducer(reducer, initialState);

  const fetchNotes = async () => {
    try {
      const notesData = await API.graphql({
        query: listNotes
      });
      dispatch({ type: "SET_NOTES", notes: notesData.data.listNotes.items });
    }
    catch (err) {
      console.log("Fetch Error :", err);
      dispatch({ type: "ERROR" });
    }
  }

  const createNote = async () => {
    const {form} = state;
    const originNotes = [...state.notes];

    // validate user input
    if (!form.name || !form.description) {
      return alert("please enter a name and description");
    }

    // optimistic response : API 호출 전에 클라이언트 업데이트
    const note = { ...form, clientId: CLIENT_ID, completed: false, id: uuid()};
    dispatch({type: "ADD_NOTE", note });
    dispatch({type: "RESET_FORM"});

    try{
      await API.graphql({
        query: CreateNote,
        variables: {input: note}
      });
      console.log("note created successfully!");
    } catch (err) {
      console.log("Fail to create note : ", err);
      dispatch({type:"SET_NOTES", notes: originNotes});
    }
  }

  const deleteNote = async ({id}) => {
    const originNotes = {...state.notes};

    const idx = state.notes.findIndex(note => note.id === id);
    const notes = [
      ...state.notes.slice(0, idx),
      ...state.notes.slice(idx+1)
    ];

    // optimistic response
    dispatch({type:"SET_NOTES", notes});

    try {
      await API.graphql({
        query: DeleteNote,
        variables: {input: {id}}
      });
      console.log("note deleted successfully!");
    }
    catch (err) {
      console.log("Fail to delete note :", err);
      dispatch({type:"SET_NOTES", notes: originNotes});
    }
  }

  const updateNote = async (note) => {
    const originNotes = [...state.notes];

    const idx = state.notes.findIndex(n => n.id == note.id);
    const notes = [...state.notes];
    notes[idx].completed = !note.completed;

    // optimistic response
    dispatch({type: "SET_NOTES", notes });
    try {
      await API.graphql({
        query: UpdateNote,
        variables: {input: {
          id: notes[idx].id,
          completed: notes[idx].completed
        }}
      });
      console.log("note updated successfully!");
    }
    catch (err) {
      console.log("Fail to update note :", err);
      dispatch({type:"SET_NOTES", notes: originNotes});
    }
  }


  const onChangeInput = (e) => {
    dispatch({type: "SET_INPUT", name: e.target.name, value: e.target.value })
  };

  // call api at first
  useEffect(() => {
    fetchNotes();

    // subscribe the create event
    const subscription = API.graphql({
      query: onCreateNote
    }).subscribe({
      next: noteData => {
        console.log("subscription",noteData);
        const note = noteData.value.data.onCreateNote;

        // 노트가 현재 클라이언트가 작성한 것이면 무시 : 이미 렌더링됨
        if (CLIENT_ID == note.clientId) return;
        dispatch({type: "ADD_NOTE", note})
      }
    })

    // 마운트 해제 시, 구독 해제
    return ()=> subscription.unsubscribe();
  }, []);

  // rendering function for each element
  const renderItem = (item) => {
    return (
      <List.Item 
        style={styles.item}
        actions={[
          <p style={styles.p} onClick={()=> updateNote(item)}>
            {item.completed? "done" : "doing"}
          </p>,
          <p style={styles.p} onClick={()=> deleteNote(item)}>Delete</p>
        ]}
      >
        <List.Item.Meta
          title={item.name}
          description={item.description}
        />
      </List.Item>
    )
  }

  return (
    <div style={styles.container}>
      <Input
        onChange={onChangeInput}
        value={state.form.name}
        placeholder="Note Name"
        name="name"
        style={styles.input}
      />
      <Input
        onChange={onChangeInput}
        value={state.form.description}
        placeholder="Note Description"
        name="description"
        style={styles.input}
      />
      <Button 
        onClick={createNote}
        type="primary"
      >Create Note</Button>
      <List
        loading={state.loading}
        dataSource={state.notes}
        renderItem={renderItem}
      />
    </div>
  );
}


export default App;
