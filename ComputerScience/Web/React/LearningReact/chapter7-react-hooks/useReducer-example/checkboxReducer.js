import React, { useReducer } from "react";

const CheckBoxReducer = () => {
    const [checked, toggle] = useReducer(checked => !checked, false);


    return (
        <>
            <input 
                type="checkbox"
                value={checked}
                onChange={toggle}
            />
            {checked? "checked" : "not checked"}
        </>
    )
}

export default CheckBoxReducer;