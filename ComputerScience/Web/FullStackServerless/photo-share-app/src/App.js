import React, { useState } from "react";
import { Radio } from "antd";
import { withAuthenticator, AmplifySignOut } from "@aws-amplify/ui-react";
import Posts from "./Posts";
import CreatePost from "./CreatePost";

const container = {
  width: "500px",
  margin: "0 auto",
  padding: "50px"
};

const App = () => {
  const [viewState, updateViewState] = useState("viewPosts");

  const onChangeRadio = (e) => {
    updateViewState(e.target.value);
  }

  return (
    <div style={container}>
      <h1>Photo Share App</h1>
      <Radio.Group
        value={viewState}
        onChange={onChangeRadio}
      >
        <Radio.Button value="viewPosts">View Posts</Radio.Button>
        <Radio.Button value="uploadPost">Upload Post</Radio.Button>
      </Radio.Group>
      {
        viewState === "viewPosts" ?
          (<Posts />) :
          (<CreatePost updateViewState={updateViewState} />)
      }
      <AmplifySignOut/>
    </div>
  );
}

export default withAuthenticator(App);
