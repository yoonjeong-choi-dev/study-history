import { Auth } from "aws-amplify";

export const signIn = async ({ username, password }, setUser) => {
    try{
        const user = await Auth.signIn(username, password);
        const userInfo = {username: user.username, ...user.attributes};
        setUser(userInfo);
    } catch (e) {
        console.error("Fail to sign in", e.name);
    }
};

export const signUp = async ({ username, password, email, description }, updateFormType) => {
    try{
        await Auth.signUp({
            username, 
            password, 
            attributes: {
                email,
                "custom:description": description
            }
        });
        console.log("Success to sign up!");
        updateFormType("confirmSignUp");
    } catch (e) {
        if (e.name === "InvalidPasswordException"){
            alert("Password not long enough!");
        } else if(e.name === "UsernameExistsException"){
            alert("User alread exits!");
        }
        else{
            console.error("Fail to sign up", e.name);
        }
        
    }
}

export const confirmSignUp = async ({ username, confirmationCode }, updateFormType) => {
    try{
        await Auth.confirmSignUp(username, confirmationCode);
        updateFormType("signIn");
    } catch (e) {
        if( e.name === "CodeMismatchException") {
            alert("Wrong Code!");
        }else{
            console.error("Fail to confirmSignUp...", e.name);
        }
    }
}

export const forgotPassword = async ({ username}, updateFormType) => {
    try{
        await Auth.forgotPassword(username);
        updateFormType("forgotPasswordSubmit");
    } catch(e) {
        console.error("Fail to submit username to reset password...", e.name);
        //updateFormType("signIn");
    }
}

export const forgotPasswordSubmit = async ({ username, confirmationCode, password }, updateFormType) => {
    try{
        await Auth.forgotPasswordSubmit(username, confirmationCode, password);
        updateFormType("signIn");
    } catch(e) {
        if( e.name === "CodeMismatchException") {
            alert("Wrong Code!");
        }else{
            console.error("Fail to update password", e.name);
        }
    }
}