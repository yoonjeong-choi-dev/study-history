import React from "react";
import { Link } from "react-router-dom";
import { commonStyles } from "./styles";

const Main = () => {
    return (
        <div style={commonStyles.container}>
            <h1>Main Page</h1>
            <Link to="/auth">
                <h2>Cognito Trigger Page</h2>
            </Link>
            <Link to="/s3">
                <h2>S3 Trigger Page</h2>
            </Link>
        </div>
    );
}

export default Main;