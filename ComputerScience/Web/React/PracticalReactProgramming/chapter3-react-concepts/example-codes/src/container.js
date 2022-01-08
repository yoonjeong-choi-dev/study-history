import React from "react";

const Container = ({title, children}) => {
    return (
        <div style={{ marginBottom: '10px', padding: '10px', border: '2px solid black'}}>
            <h2>{title}</h2>
            {children}
        </div>
    )
};

export default Container;