import React from "react";

export default function Agreement({ onAgree = f=>f }) {
    return (
        <div>
            <h1>Terms..</h1>
            <h2>These are the terms and stuff. Do you agree?</h2>
            <button onClick={onAgree}>I agree</button>
        </div>
    );
}