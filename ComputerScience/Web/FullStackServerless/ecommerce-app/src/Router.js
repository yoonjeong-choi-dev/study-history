/*
각 페이지 라우팅 관련 컴포넌트
- 사용 가능한 컴포넌트와 경로 정의
- window.location.href 속성을 이용하여 현재 경로 이름 설정하여 Nav로 전달

사용하는 컴포넌트
1. HashRouter
  : URL의 해시를 사용하여 UI를 URL과 일치하도록 유지하는 라우터
2. Switch
  : 현재 위치에 매칭되는 자식 Route 컴포넌트 렌더링
3. Route
  : 경로 기반으로 렌더링할 컴포넌트 정의
*/

import React, { useState, useEffect } from "react";
import { HashRouter, Routes, Route } from "react-router-dom";

import Nav from "./Nav";
import Main from "./Main";
import Profile from "./Profile";
import Admin from "./Admin";

const Router = () => {
    const validPaths = ["home", "admin", "profile"];

    // 경로 상태 관리
    const [current, setCurrent] = useState("home");

    const setRoute = () => {
        // 현재 URL에서 마지막 / 이후의 path 경로 추출
        const location = window.location.href.split("/");
        let pathName = location[location.length - 1];

        // 유효하지 않은 URL에 대해서는 디폴트로 /home 경로 설정
        if (!pathName || !validPaths.includes(pathName)){
          console.log("Invalid Path : ", pathName)
          pathName = "home";
        }
        setCurrent(pathName);
    }

    // URL 해시 관련 이벤트 리스너를 마운트 시 등록
    useEffect(() => {
        setRoute();

        // 해시 변경 시 경로 상태 변경 이벤트 리스너 등록
        window.addEventListener("hashchange",setRoute, false);

        // 마운트 해제 시, 이벤트 구독 해제
        return () => window.removeEventListener("hashchange", setRoute);
    }, []);

    return (
        <HashRouter>
            <Nav current={current} />
            <Routes>
                <Route exact path="/" element={<Main />} />
                <Route exact path="/admin" element={<Admin />} />
                <Route exact path="/profile" element={<Profile/>} />
                <Route path="*" element={<Main />} />
            </Routes>
        </HashRouter>
    );
};

export default Router;