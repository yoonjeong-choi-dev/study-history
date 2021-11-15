import React from "react";
import { commonStyles } from "./styles";
import { useNavigate } from "react-router";
import ImageUploadForm from "./ImageUploadForm"

const S3ImageUpload = () => {
    const navigate = useNavigate();

    const goBack = () =>{
        navigate("/");
    }

    return (
        <div style={commonStyles.container}>
            <h1>S3 Trigger Test</h1>
            <button style={commonStyles.button} onClick={goBack}>
                Go back
            </button>
            <ImageUploadForm/>
        </div>
    )
};

export default S3ImageUpload;