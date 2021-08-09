import {useState, useEffect, useMemo, useCallback} from "react";

const useFetch = (uri) => {
    const [data, setData] = useState();
    const [error, setError] = useState();
    const [loading, setLoading] = useState(true);

    useEffect( ()=> {
        if (!uri) return;

        fetch(uri)
            .then(resp => resp.json())
            .then(setData)
            .then(() =>setLoading(false))
            .catch(setError);
    }, [uri]);

    return {
        loading,
        data,
        error
    };
}

const useIterator = (items=[], initialIndex=0) => {
    const [index, setIndex] = useState(initialIndex);

    const prev = useCallback(() => {
        if (index === 0) return setIndex(items.length -1);
        setIndex(index-1);
    }, [index]);

    const next = useCallback( () => {
        if (index === items.length -1) return setIndex(0);
        setIndex(index+1);
    }, [index]);

    const item = useMemo(()=>items[index], [index]);

    return [item, prev, next];
}

export {useFetch, useIterator};