import React from "react";
import { useInput } from "./hooks";

const SearchForm = ({onSearch}) => {
    const [userInput, resetInput] = useInput("");

    const submit = e=> {
        e.preventDefault();
        onSearch(userInput.value);
        resetInput();
    };

    return (
        <form onSubmit={submit}>
                <input {...userInput} type="text" placeholder="Github user" required />
                <button style={{paddingLeft: "10px"}}>Login</button>
        </form>
    )
}

export default SearchForm;