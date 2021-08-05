import React, {useState, useEffect } from "react";

const TwoStateEffect = () => {
    const [val, setVal] = useState("");
    const [phrase, setPhrase] = useState("example phrase");

    const createPhrase = () => {
        setPhrase(val);
        setVal("");
    };

    useEffect(()=>{
        console.log("TwoStateEffect Component is loaded");
        return ()=> {console.log("TwoStateEffect Component is unloaded")};
    },[]);

    useEffect(()=>{
        console.log(`typing "${val}"`);
    }, [val]);

    useEffect(()=>{
        console.log(`saved phrase: "${phrase}"`);
    }, [phrase]);

    return (
        <>
            <label>Favorite Phrase</label>
            <input 
                value={val}
                placeholder={phrase}
                onChange = {e=> setVal(e.target.value)}
            />
            <button onClick={createPhrase}>send</button>
        </>
    )
}

export default TwoStateEffect;