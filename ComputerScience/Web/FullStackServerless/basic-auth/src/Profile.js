/*
로그인한 사용자에 대한 프로필 컴포넌트
- 사용자 가입 및 로그인을 위한 인증 컴포넌트 포함
- 비로그인 시 : 로그인 양식 출력
- 로그인 시
  - 로그아웃 버튼 제공
  - 사용자 정보 렌더링
*/

import React, { useState, useEffect } from "react";
import { Auth, Hub } from "aws-amplify";
import { Button } from "antd";
import Container from "./Container"
import Form from "./LoginForm/Form";

const Profile = () => {
    // 로그인한 유저에 대한 상태 관리
    const [user, setUser] = useState(null);

    // 로그인 여부 확인
    const checkUser = async () => {
        try {
            // 유저 정보 fetch
            const data = await Auth.currentUserPoolUser();
            console.log(data);
            const userInfo = { username: data.username, ...data.attributes };
            setUser(userInfo);
        }
        catch (err) {
            console.log("Fail to check user : ", err);
        }
    }

    const signOut = () => {
        Auth.signOut()
            .catch(err => console.error("Fail to logout", err));
    }

    // 마운트 시, 로그인 여부 확인
    useEffect(() => {
        checkUser();
        Hub.listen("auth", (data) => {
            const { payload } = data;
            if (payload.event === "signOut") {
                setUser(null);
            }
        })
    }, []);

    if (user) {
        return (
            <Container>
                <h1>Profile</h1>
                <h2>Username: {user.username}</h2>
                <h3>Email: {user.email}</h3>
                <h3>Phone: {user.phone_number}</h3>
                <h3>Description: {user["custom:description"]}</h3>
                <Button onClick={signOut}>Sign Out</Button>
            </Container>
        )
    }
    else {
        return <Form setUser={setUser} />
    }
};

export default Profile;