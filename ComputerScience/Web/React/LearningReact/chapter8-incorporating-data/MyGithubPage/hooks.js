import {useState, useEffect, useMemo, useCallback, useRef} from "react";

const useInput = (initValue) => {
    const [value, setValue] = useState(initValue);
    return [
        {
            value, 
            onChange: e => setValue(e.target.value)
        },
        () => setValue(initValue)
    ];
};

const useMountedRef = () => {
    const mounted = useRef(false);
    useEffect( ()=> {
        mounted.current = true;
        return ()=> (mounted.current = false);
    });
    return mounted;
}

const useFetch = (uri) => {
    const mounted = useMountedRef();

    const [data, setData] = useState();
    const [error, setError] = useState();
    const [loading, setLoading] = useState(true);


    useEffect( ()=> {
        if (!uri) return;
        if (!mounted.current) return;

        fetch(uri)
            .then(resp => {
                if(!mounted.current) throw new Error("component is not mounted!");
                return resp;
            })
            .then(resp => resp.json())
            .then(setData)
            .then(() =>setLoading(false))
            .catch(error=>{
                if(!mounted.current) return;
                setError(error);
            });
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




export {useInput, useFetch, useIterator, useMountedRef};