import React, {useState, useEffect } from "react";
import { withAuthenticator, AmplifySignOut } from "@aws-amplify/ui-react";
import { Auth } from "aws-amplify";

const titleStyle = {
    fontWeight: "normal",
    margin: "0px 0px 10px 0px"
};

const Admin = () => {
    const [user, updateUser] = useState(null);
    useEffect(() => {
        Auth.currentAuthenticatedUser()
            .then(user => {
                console.log("USER : ", user);
                return updateUser(user);
            })
            .catch(err => console.log("Need to login"));
    }, []);

    let isAdmin = false;
    if (user) {
        const { signInUserSession: { idToken: { payload } } } = user;
        console.log("payload: ", payload);

        // 관리자인지 확인
        if (payload["cognito:groups"] && payload["cognito:groups"].includes("Admin")) {
            isAdmin = true;
        }
    }

    return (
        <div>
            <h1 style={titleStyle}>Admin</h1>
            {
                isAdmin ?
                    <h3>Welcome, Admin</h3> :
                    <h3>Welcome, User</h3>
            }
            <AmplifySignOut/>
        </div>
    );
};

export default withAuthenticator(Admin);