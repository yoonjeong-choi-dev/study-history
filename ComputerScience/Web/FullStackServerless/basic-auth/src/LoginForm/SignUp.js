// 가입 양식 컴포넌트

import React from "react";
import Button from "./Button";
import { formStyles } from "./styles";

const SignUp = ({ updateFormState, singUp }) => {
    const onChange = (e) => {
        e.persist();
        updateFormState(e);
    };


    return (
        <div style={formStyles.container}>
            <input
                name="username"
                onChange={onChange}
                style={formStyles.input}
                placeholder="username"
            />
            <input
                type="password"
                name="password"
                onChange={onChange}
                style={formStyles.input}
                placeholder="password"
            />
            <input
                name="email"
                onChange={onChange}
                style={formStyles.input}
                placeholder="email"
            />
            <input
                name="description"
                onChange={onChange}
                style={formStyles.input}
                placeholder="description"
            />
            <Button onClick={singUp} title="Sign Up" />
        </div>
    );
}

export default SignUp;