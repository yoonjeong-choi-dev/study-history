import React, { useState, useEffect } from "react";

const CheckBox = () => {
    const [checked, setChecked ] = useState(false);

    useEffect( ()=> {
        console.log(`checked: ${checked.toString()}`);
    });
    

    const onChange = () => setChecked(checked => !checked);

    return (
        <>
            <input 
                type="checkbox"
                value={checked}
                onChange={onChange}
            />
            {checked? "checked" : "not checked"}
        </>
    )
}

export default CheckBox;