import React, {useEffect} from "react";
import { useIterator } from "./hooks";
import RepositoryReadMe from "./RepositoryReadMe";

const RepositoryMenu = ({login, respositories, onSelect=f=>f}) => {
    const [{name}, previous, next ] = useIterator(respositories);

    useEffect(() => {
        if (!name) return;
        onSelect(name);
    }, [name]);

    return (
        <>
            <div style={{display: "flex"}}>
                <button onClick={previous}>&lt;</button>
                <p>{name}</p>
                <button onClick={next}>&gt;</button>
            </div>
            <RepositoryReadMe login={login} repo={name}/>
        </>
    )
}

export default RepositoryMenu;