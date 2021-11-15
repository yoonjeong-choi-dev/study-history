/* eslint-disable-line */ const aws = require('aws-sdk');


exports.handler = async (event) => {
  const cognitoProvider = new aws.CognitoIdentityServiceProvider({
    apiVersion: '2016-04-18',
  });

  let isAdmin = false;
  let adminEmails = ["yjchoi7166@gmail.com", "yjchoi7166@naver.com"];

  // 사용자가 관리자인지 이메일을 이용하여 확인
  if (adminEmails.indexOf(event.request.userAttributes.email) !== -1) {
    isAdmin = true;
  }

  const groupParams = {
    UserPoolId: event.userPoolId,
  };

  const userParams = {
    UserPoolId: event.userPoolId,
    Username: event.userName,
  };

  // 관리자인 경우에만 유저 등록
  if (isAdmin) {
    groupParams.GroupName = "Admin";
    userParams.GroupName = "Admin";

    // 그룹이 있는지 확인 후, 없으면 생성
    try {
      await cognitoProvider.getGroup(groupParams).promise();
    } catch (e) {
      console.log("Create new admin group");
      await cognitoProvider.createGroup(groupParams).promise();
    }

    // 관리자 사용자면 Admin 그룹에 추가
    try {
      await cognitoProvider.adminAddUserToGroup(userParams).promise();
    } catch (e) {
      console.log("Fail to adminAddUserToGroup", e);
    }
  } else {
    // 사용자가 관리자가 아닌 경우에는 아무 작업도 하지 않음
  }

  const response = {
    statusCode: 200,
    body: event
  };

  return response;
};
