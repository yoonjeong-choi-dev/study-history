import React, { useState, useEffect } from "react";
import { HashRouter, Routes, Route } from "react-router-dom";

import Nav from "./Nav";
import Home from "./Home";
import Admin from "./Admin";
import Footer from "./Footer";
import Container from "./Container";
import Performance from "./Performance";

const Router = () => {
    const validPaths = ["home", "admin", "performance"];
    const [current, setCurrent] = useState("home");

    const setRoute = () => {
        // 현재 URL에서 마지막 / 이후의 path 경로 추출
        const location = window.location.href.split("/");
        let pathName = location[location.length - 1];

        // 유효하지 않은 URL에 대해서는 디폴트로 /home 경로 설정
        if (!pathName) {
            console.log("Invalid Path : ", pathName)
            pathName = "home";
        }
        setCurrent(pathName);
    };

    useEffect(() => {
        setRoute();
        // 해시 변경 시 경로 상태 변경 이벤트 리스너 등록
        window.addEventListener("hashchange", setRoute, false);
        // 마운트 해제 시, 이벤트 구독 해제
        return () => window.removeEventListener("hashchange", setRoute);
    }, []);

    return (
        <HashRouter>
            <Nav current={current} />
            <Container>
                <Routes>
                    <Route exact path="/" element={<Home />} />
                    <Route exact path="/performance/:id" element={<Performance />} />
                    <Route exact path="/admin" element={<Admin />} />
                    <Route path="*" element={<Home />} />
                </Routes>
            </Container>
            <Footer/>
        </HashRouter>
    );
};

export default Router;