import React, {useEffect} from "react";
import { useIterator } from "./hooks";

const RepositoryMenu = ({respositories, selectedRepo, onSelect=f=>f}) => {
    const [{name}, previous, next ] = useIterator(
        respositories,
        selectedRepo? respositories.findIndex(repo=> repo.name === selectedRepo) : null
    );
    
    

    useEffect(() => {
        if (!name) return;
        onSelect(name);
    }, [name]);

    return (
        <div style={{display: "flex"}}>
            <button onClick={previous}>&lt;</button>
            <p>{name}</p>
            <button onClick={next}>&gt;</button>
        </div>

    )
}

export default RepositoryMenu;