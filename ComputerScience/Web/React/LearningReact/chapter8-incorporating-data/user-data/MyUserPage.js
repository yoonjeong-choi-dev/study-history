import React, { useState } from "react";
import { useInput } from "./hooks";
import PureUser from "./User";


const MyUserPage = () => {
    const [nameInput, resetNameInput] = useInput("");
    const [id, setId] = useState("");


    const submit = e=> {
        e.preventDefault();
        setId(nameInput.value);
        resetNameInput();
    };

    return (
        <> 
            <form onSubmit={submit}>
                <input {...nameInput} type="text" placeholder="Github user" required />
                <button style={{paddingLeft: "10px"}}>Login</button>
            </form>
            <PureUser userId={id} />
        </>
    )
}

export default MyUserPage;