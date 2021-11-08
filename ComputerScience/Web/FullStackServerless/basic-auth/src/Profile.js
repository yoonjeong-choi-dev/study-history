/*
로그인한 사용자에 대한 프로필 컴포넌트
- 사용자 가입 및 로그인을 위한 인증 컴포넌트 포함
- 비로그인 시 : 로그인 양식 출력
- 로그인 시
  - 로그아웃 버튼 제공
  - 사용자 정보 렌더링
*/

import React, { useState, useEffect } from "react";
import { Auth } from "aws-amplify";
import { withAuthenticator, AmplifySignOut } from "@aws-amplify/ui-react";
import Container from "./Container"

const Profile = () => {
    // 로그인한 유저에 대한 상태 관리
    const [user, setUser] = useState({});

    // 로그인 여부 확인
    const checkUser = async () => {
        try {
            // 유저 정보 fetch
            const data = await Auth.currentUserPoolUser();
            const userInfo = { username: data.username, ...data.attributes };
            setUser(userInfo);
        }
        catch (err) {
            console.log("check user : ", err);
        }
    }

    // 마운트 시, 로그인 여부 확인
    useEffect(() => {
        checkUser();
    }, []);

    return (
        <Container>
            <h1>Profile</h1>
            <h2>Username: {user.username}</h2>
            <h3>Email: {user.email}</h3>
            <h3>Phone: {user.phone_number}</h3>
            <AmplifySignOut/>
        </Container>
    )
};

export default withAuthenticator(Profile);