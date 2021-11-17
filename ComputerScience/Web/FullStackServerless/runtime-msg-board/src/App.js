import React, { useState, useEffect } from "react";
import { SketchPicker } from "react-color";
import { Input, Button } from "antd";
import { DataStore } from "@aws-amplify/datastore";
import { Message } from "./models";
import styles from "./styles";

const initialState = {
  color: "#000000",
  title: "",
  user: ""
}


function App() {
  const [formState, updateFormState] = useState(initialState);
  const [messages, updateMessages] = useState([]);
  const [showPicker, updateShowPicker] = useState(false);

  const fetchMessages = async () => {
    const data = await DataStore.query(Message);
    updateMessages(data);
  }

  const createMessage = async () => {
    if (!formState.user) {
      alert("Please enter your name!");
      return;
    }
    if (!formState.title) {
      alert("Please enter title");
      return;
    }

    await DataStore.save(new Message({ ...formState }));
    updateFormState(
      {
        ...initialState,
        user: formState.user
      }
    );
  }

  useEffect(() => {
    fetchMessages();

    // 새로운 메시지가 등록되면 다시 fetch
    const subscription = DataStore.observe(Message).subscribe(() => fetchMessages());

    // 마운트 해제시 구독 해제
    return () => subscription.unsubscribe();
  }, []);

  const onChangeInput = (e) => {
    if (e.hex) {
      updateFormState({ ...formState, color: e.hex });
    } else {
      updateFormState({
        ...formState,
        [e.target.name]: e.target.value
      });
    }
  }

  return (
    <div style={styles.container}>
      <h1 style={styles.heading}>Real Time Message Board</h1>
      <Input
        onChange={onChangeInput}
        name="user"
        placeholder="User name"
        value={formState.user}
        style={styles.input}
      />
      <Input
        onChange={onChangeInput}
        name="title"
        placeholder="Message Title"
        value={formState.title}
        style={styles.input}
      />
      <div>
        <Button
          onClick={() => updateShowPicker(!showPicker)}
          style={styles.button}
        >Toggle Color Picker</Button>

        <p>
          Color :
          <span style={{ fontWeight: "bold", color: formState.color }}>
            {formState.color}
          </span>
        </p>
      </div>
      {
        showPicker && (
          <SketchPicker
            color={formState.color}
            onChange={onChangeInput} />
        )
      }
      <Button type="primary" onClick={createMessage}>Send Message</Button>
      {
        messages.map(message => (
          <div
            key={message.id}
            style={{ ...styles.messageStyle, backgroundColor: message.color }}
          >
            <div style={styles.messageBackground}>
              <p style={styles.messageUser}>{message.user}</p>
              <p style={styles.messageTitle}>{message.title}</p>
            </div>
          </div>
        ))
      }
    </div>
  )

}

export default App;
