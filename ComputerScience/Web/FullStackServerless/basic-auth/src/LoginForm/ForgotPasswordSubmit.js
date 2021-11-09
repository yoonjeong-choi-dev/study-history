// 비밀번호를 재설정하는 양식 컴포넌트

import React from "react";
import Button from "./Button";
import { formStyles } from "./styles";


const ForgotPasswordSubmit = (props) => {
    const onChange = (e) => {
        e.persist();
        props.updateFormState(e);
    };

    return (
        <div style={formStyles.container}>
            <input
                name="confirmationCode"
                onChange={onChange}
                style={formStyles.input}
                placeholder="confirmationCode"
            />
            <input
                name="password"
                type="password"
                onChange={onChange}
                style={formStyles.input}
                placeholder="password"
            />
            <Button onClick={props.forgotPasswordSubmit} title="Save new Password" />
        </div>
    );
}

export default ForgotPasswordSubmit;