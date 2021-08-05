import React, {useEffect, useMemo} from "react";
import useAnykeyToRender from "../useEffect-example/useAnykeyToRender";


const WithUseMemo = ({children ="" }) => {
    useAnykeyToRender();

    // children 변수가 변경될 때만, words 리스트 변경
    const words = useMemo(()=>{
        return children.split(" ");
    }, [children]);

    useEffect(()=> {
        console.log("With UseMemo : Fresh Render");
    }, [words]);

    return (
        <>
            <h1>With UseMemo : Open Console log</h1>
            <p>{children}</p>
            <p><strong>{words.length} - words</strong></p>
        </>
    )
};

export default WithUseMemo;