// 로그인 여부와 상관없이 접근 가능한 페이지

import React from "react";
import Container from "./Container";

const Public = () => {
    return (
        <Container>
            <h1>Public Route</h1>
            <h2>Anyone can access!</h2>
        </Container>
    )
};

export default Public;