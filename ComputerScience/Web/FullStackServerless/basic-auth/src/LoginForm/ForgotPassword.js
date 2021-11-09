// 비밀번호를 찾기 위해 사용자 이름을 입력하는 양식

import React from "react";
import Button from "./Button";
import { formStyles } from "./styles";


const ForgotPassword = (props) => {
    const onChange = (e) => {
        e.persist();
        props.updateFormState(e);
    };

    return (
        <div style={formStyles.container}>
            <input
                name="username"
                onChange={onChange}
                style={formStyles.input}
                placeholder="username"
            />
            <Button onClick={props.forgotPassword} title="Reset Password" />
        </div>
    );
}

export default ForgotPassword;