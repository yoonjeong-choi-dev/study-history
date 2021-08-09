import React from "react";
import { useFetch } from "./hooks";

const Fetch = ({
    uri,
    renderSuccess,
    laodingFallback = <p>loading...</p>,
    renderError = error => (
        <pre>{JSON.stringify(error, null, 2)}</pre>
    )
}) => {
    const {loading, data, error } = useFetch(uri);

    if (loading) return laodingFallback;
    if (error) return renderError(error);
    if (data) return renderSuccess({data});
}

export default Fetch;