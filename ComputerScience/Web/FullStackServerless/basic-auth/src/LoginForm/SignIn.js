// 로그인 양식 컴포넌트

import React from "react";
import Button from "./Button";
import { formStyles } from "./styles";

const SignIn = ({ signIn, updateFormState }) => {
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
            <Button onClick={signIn} title="Sign In" />
        </div>
    );
};

export default SignIn;