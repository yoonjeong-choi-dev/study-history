/*
보호된 페이지에 해당하는 컴포넌트
- 로그인한 유저만 접근 가능
- 비로그인 시, 로그인 양식으로 리다이렉트
*/

import React, { useEffect } from "react";
import { useNavigate } from "react-router-dom";
import { Auth } from "aws-amplify";
import Container from "./Container";

const Protected = () => {
    const navigate = useNavigate();
    const checkLogin = async () => {
        // API 호출을 이용한 로그인 여부 확인
        // 에러 발생 <=> 비로그인 상태
        await Auth.currentAuthenticatedUser().catch(() => {
            navigate("/profile");
        });
    };

    // 마운트 시, 로그인 여부 확인 : 비로그인 시 로그인 페이지로 리다이렉트
    useEffect(() => {
        checkLogin();
    }, []);

    return (
        <Container>
            <h1>Protected Route</h1>
            <h2>Only login user can access!</h2>
        </Container>
    );
};

export default Protected;