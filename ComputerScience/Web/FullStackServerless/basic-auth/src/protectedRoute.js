/*
인증이 필요한 모든 경로를 보호하는데 사용하는 훅
- 인증이 필요한 컴포넌트를 인자로 받아 컴포넌트 반환하는 훅
- 이전에 Protected 컴포넌트에서 사용했던 로직을 해당 훅에서 수행
  - 로그인 유저에게는 인자로 받은 컴포넌트 실행
  - 비로그인 유저는 
*/

import React, {useEffect } from "react";
import { useNavigate } from "react-router-dom";
import { Auth } from "aws-amplify";

const protectedRoute = ( Comp, route="/profile" ) => (props) => {
    const navigate = useNavigate();
    const checkLogin = async () => {
        // API 호출을 이용한 로그인 여부 확인
        // 에러 발생 <=> 비로그인 상태
        await Auth.currentAuthenticatedUser().catch(() => {
            navigate(route, { replace: true });
        });
    };
    
    // 마운트 시, 로그인 여부 확인 : 비로그인 시 로그인 페이지로 리다이렉트
    useEffect(() => {
        checkLogin();
    }, []);

    return <Comp {...props} />;
}


export default protectedRoute;