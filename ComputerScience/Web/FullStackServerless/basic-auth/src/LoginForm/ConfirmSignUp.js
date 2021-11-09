// 사용자 가입 후 MFA 확인 코드 입력하는 컴포넌트

import React from "react";
import Button from "./Button";
import { formStyles } from "./styles";

const ConfirmSignUp = (props) => {
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
        <Button onClick={props.confirmSignUp} title="Confirm Sign Up" />
    </div>
    )
}

export default ConfirmSignUp;