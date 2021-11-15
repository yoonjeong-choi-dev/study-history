/*
로그인한 사용자에 대한 프로필 컴포넌트
- 사용자 가입 및 로그인을 위한 인증 컴포넌트 포함
- 비로그인 시 : 로그인 양식 출력
- 로그인 시
  - 로그아웃 버튼 제공
  - 사용자 정보 렌더링
*/

import React from "react";
import { withAuthenticator,AmplifySignOut } from "@aws-amplify/ui-react";

const containerStyle = {
  width: "400px",
  margin: "20px auto"
}

const Profile = () => {
  return (
    <div style={containerStyle}>
      <AmplifySignOut />
    </div>
  );
};

export default withAuthenticator(Profile);