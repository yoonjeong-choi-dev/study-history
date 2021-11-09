/*
보호된 페이지에 해당하는 컴포넌트
- 로그인한 유저만 접근 가능
- 비로그인 시, 로그인 양식으로 리다이렉트
*/

import React from "react";
import Container from "./Container";
import protectedRoute from "./protectedRoute";

const Protected = () => {
    return (
        <Container>
            <h1>Protected Route</h1>
            <h2>Only login user can access!</h2>
        </Container>
    );
};

export default protectedRoute(Protected);