import React, {useState} from "react";
import WithoutUseMemo from "./WithoutUseMemo";
import WithUseMemo from "./WithUseMemo";

const UseMemoExample = () => {
    const [val, setVal] = useState("");

    const OnClickButton = () => {
        setVal(val + "Test ");
    }

    return (
        <>
           <button onClick={OnClickButton}>children props change</button>
            <div>Press any key : only "WithoutUseMemo" component will re-render</div>
            <div className="App">
                <WithoutUseMemo>
                    {val}
                </WithoutUseMemo>
                <WithUseMemo>
                    {val}
                </WithUseMemo>
            </div>
        </>
    )
}

export default UseMemoExample;