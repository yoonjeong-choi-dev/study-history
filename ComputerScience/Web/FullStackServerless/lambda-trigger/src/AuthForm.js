import React, { useEffect, useState } from "react";
import { commonStyles } from "./styles";
import { useNavigate } from "react-router";
import UserInfo from "./UserInfo";

const AuthForm = () => {
    const navigate = useNavigate();
    const goBack = () =>{
        navigate("/");
    }


    return (
        <div style={commonStyles.container}>
            <h1>Cognito Trigger Test</h1>
            <button style={commonStyles.button} onClick={goBack}>
                Go back
            </button>
            <div style={{width:"460px", height:"540px", textAlign:"left"}}>
            <UserInfo/>
            </div>
            
            
        </div>
    )
};

export default AuthForm;