import React, {useState} from "react";
import PureCompoent, {MyComponent} from "./pureComponent";

const PureComponentExample = () => {
    const [cats, setCats] = useState(["Cat1", "Cat2", "Cat3"]);

    return (
        <>
            <h1>Check console log!!!</h1>
            <button onClick= { ()=> setCats([...cats, prompt("Name a cat :")])}>
                Add a Cat
            </button>
            <h2>Not Pure Component</h2>
            {cats.map((name, idx) => (
                <MyComponent key={idx} name={name} clicking={name=>console.log(`${name} has clicked`)} />
            ))}
            <h2>Pure Component</h2>
            {cats.map((name, idx) => (
                <PureCompoent key={idx} name={name} clicking={name=>console.log(`${name} has clicked`)} />
            ))}
            
        </>
    )
}

export default PureComponentExample;