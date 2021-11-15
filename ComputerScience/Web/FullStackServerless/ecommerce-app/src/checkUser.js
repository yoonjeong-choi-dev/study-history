// API를 통해 현재 사용자 정보를 확인하여 updateUser를 이용하여 사용자 정보 업데이트
import { Auth } from "aws-amplify";

const checkUser = async (updateUser) => {
    const userData = await Auth.currentSession()
        .catch(err => console.log("No login user : ", err));

    // 로그인 유저가 없는 경우 사용자 정보를 빈 객체로 업데이트
    if (!userData) {
        console.log("Current User Data : ", userData);
        updateUser({});
        return;
    }

    // 사용자가 속해 있는 Cognito 그룹 확인 및 Admin 유저인지 확인
    const { idToken: { payload }} = userData;
    const isAdmin = payload["cognito:groups"] && payload["cognito:groups"].includes("Admin");
    updateUser({
        username: payload["cognito:username"],
        isAdmin
    });
}

export default checkUser;