import React, {useEffect} from "react";
import useAnykeyToRender from "../useEffect-example/useAnykeyToRender";


const WithoutUseMemo = ({children ="" }) => {
    useAnykeyToRender();

    const words = children.split(" ");

    useEffect(()=> {
        console.log("Without UseMemo : Fresh Render");
    }, [words]);

    return (
        <>
            <h1>Without UseMemo :Open Console log</h1>
            <p>{children}</p>
            <p><strong>{words.length} - words</strong></p>
        </>
    )
};

export default WithoutUseMemo;