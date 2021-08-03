import React from "react";
import ColorProvider from "./color-hooks"
import AddColorForm from "./AddColorForm";
import ColorList from "./ColorList";

const ColorListExampleWithContext = () => {
    
    return (
        <ColorProvider>
            <AddColorForm/>
            <ColorList/>
        </ColorProvider>
    );
};

export default ColorListExampleWithContext;