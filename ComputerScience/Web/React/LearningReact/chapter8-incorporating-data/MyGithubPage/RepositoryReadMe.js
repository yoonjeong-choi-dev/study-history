import React, { useState, useEffect, useCallback } from "react";
import ReactMarkdown from "react-markdown";
import { useMountedRef } from "./hooks";

const RepositoryReadMe = ({login, repo}) => {
    const [loading, setLoading] = useState(false);
    const [error, setError] = useState();
    const [markdown, setMarkdown] = useState("");

    // 상태 갱신 이전에 마운트 확인을 위한 상태 변수
    const mounted = useMountedRef()

    // readme.md 파일 경로를 얻어와 해당 경로로 다시 호출하여 readme 파일을 다운 받는 함수 메모
    const loadReadme = useCallback(async (login, repo) => {
        setLoading(true);

        const uri = `https://api.github.com/repos/${login}/${repo}/readme`;
        const { download_url } = await fetch(uri).then(res => res.json());
        const markdown = await fetch(download_url).then(res => res.text());

        if(mounted.current) {
            setMarkdown(markdown);
            setLoading(false);
        }
    }, [])

    // repo 변경 시, 해당 repo에 대한 readme 상태 변경 및 리렌더링
    useEffect(() => {
        if (!repo || !login) return;
        loadReadme(login, repo).catch(setError);
      }, [repo]);
      
    
    if (error) return <pre>{JSON.stringify(error, null, 2)}</pre>;
    if (loading) return <p>Loading...</p>;

    return <ReactMarkdown children={markdown} />;
}

export default RepositoryReadMe;