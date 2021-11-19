import React, { useState } from "react";
import { Button, Input } from "antd";
import { v4 as uuid } from "uuid";
import { createPost } from "./graphql/mutations";
import { API, graphqlOperation, Storage } from "aws-amplify";


const heading = { margin: "20px 0px" };
const withMargin = { marginTop: 10 };
const button = { marginTop: 10 };

const initialFormState = {
    title: "",
    image: {}
};

const CreatePost = ({ updateViewState }) => {
    const [formState, updateFormState] = useState(initialFormState);

    const onChangeInput = (key, value) => {
        updateFormState({
            ...formState,
            [key]: value
        });
    };

    const setPhoto = (e) => {
        if (!e.target.files[0]) return;

        const file = e.target.files[0];
        updateFormState({
            ...formState,
            image: file
        });
    }

    const savePhoto = async () => {
        const { title, image } = formState;
        if (!title) {
            alert("Please enter your image title");
            return;
        }
        if (!image.name) {
            alert("Please upload your image file");
            return;
        }
        const imageKey = uuid() + image.name.replace(/\s/g, "-").toLowerCase();

        try {
            await Storage.put(imageKey, formState.image);
        } catch (e) {
            console.error("Fail to upload : ", e);
            return;
        }

        try {
            const post = { title, imageKey };
            await API.graphql(graphqlOperation(createPost, { input: post }));
        } catch (e) {
            console.error("Fail to update db : ", e);
            return;
        }

        updateViewState("viewPosts");
    }

    return (
        <div>
            <h2 styles={heading}>Add Photo</h2>
            <Input
                onChange={e => onChangeInput("title", e.target.value)}
                style={withMargin}
                placeholder="Title"
            />
            <input
                type="file"
                onChange={setPhoto}
                style={button}
            />
            <Button style={button} type="primary" onClick={savePhoto}>Upload</Button>
        </div>
    );
};

export default CreatePost;