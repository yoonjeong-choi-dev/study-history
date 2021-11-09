import React, { useState } from "react";
import { signIn, signUp, confirmSignUp, forgotPassword, forgotPasswordSubmit } from "./authAPI";
import SignIn from "./SignIn";
import SignUp from "./SignUp";
import ConfirmSignUp from "./ConfirmSignUp";
import ForgotPassword from "./ForgotPassword";
import ForgotPasswordSubmit from "./ForgotPasswordSubmit";
import { formStyles } from "./styles";


const initialFormState = {
    username: "",
    password: "",
    email: "",
    description: "",
    confirmationCode: ""
};



const Form = (props) => {
    const [formType, updateFormType] = useState("signIn");
    const [formState, updateFormState] = useState(initialFormState);

    const updateForm = (event) => {
        const newFormState = {
            ...formState,
            [event.target.name]: event.target.value
        };
        updateFormState(newFormState);
    }

    const renderForm = () => {
        switch (formType) {
            case "signIn":
                return (
                    <SignIn
                        signIn={() => signIn(formState, props.setUser)}
                        updateFormState={updateForm}
                    />
                );
            case "signUp":
                return (
                    <SignUp
                        singUp={() => signUp(formState, updateFormType)}
                        updateFormState={updateForm}
                    />
                )
            case "confirmSignUp":
                return (
                    <ConfirmSignUp
                        confirmSignUp={() => confirmSignUp(formState, updateFormType)}
                        updateFormState={updateForm}
                    />
                )
            case "forgotPassword":
                return (
                    <ForgotPassword
                        forgotPassword={() => forgotPassword(formState, updateFormType)}
                        updateFormState={updateForm}
                    />
                )
            case "forgotPasswordSubmit":
                return (
                    <ForgotPasswordSubmit
                        forgotPasswordSubmit={() => forgotPasswordSubmit(formState, updateFormType)}
                        updateFormState={updateForm}
                    />
                )
            default:
                return null;
        }
    }

    return (
        <div>
            {renderForm()}
            {
                formType === "signUp" &&
                (
                    <p style={formStyles.toggleForm}>
                        Already have an account?
                        <span
                            style={formStyles.anchor}
                            onClick={() => updateFormType("signIn")}
                        >Sign In
                        </span>
                    </p>
                )
            }
            {
                formType === "signIn" &&
                (
                    <>
                        <p style={formStyles.toggleForm}>
                            Need an account?
                            <span
                                style={formStyles.anchor}
                                onClick={() => updateFormType("signUp")}
                            >Sign Up
                            </span>
                        </p>
                    </>
                )
            }
            <p style={{ ...formStyles.toggleForm, ...formStyles.resetPassword }}>
                Forget Your Password?
                <span
                    style={formStyles.anchor}
                    onClick={() => updateFormType("forgotPassword")}
                >Reset Password
                </span>
            </p>
        </div>
    );
}

export default Form;