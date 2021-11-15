/*
Copyright 2017 - 2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License"). You may not use this file except in compliance with the License. A copy of the License is located at
    http://aws.amazon.com/apache2.0/
or in the "license" file accompanying this file. This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and limitations under the License.
*/


/* Amplify Params - DO NOT EDIT
	AUTH_ECOMMERCEAPP4FA8F000_USERPOOLID
	ENV
	REGION
	STORAGE_PRODUCTTABLE_ARN
	STORAGE_PRODUCTTABLE_NAME
	STORAGE_PRODUCTTABLE_STREAMARN
Amplify Params - DO NOT EDIT */

const AWS = require("aws-sdk");
const { v4: uuid } = require("uuid");

// Cognito SDK and env
const cognitoProvider = new AWS.CognitoIdentityServiceProvider({
  apiVersion: '2016-04-18',
});
var userpoolId = process.env.AUTH_ECOMMERCEAPP4FA8F000_USERPOOLID;

// DynamoDB SDK and env
const region = process.env.REGION;
const db_table_name = process.env.STORAGE_PRODUCTTABLE_NAME;
const db_client = new AWS.DynamoDB.DocumentClient({region});

var express = require('express')
var bodyParser = require('body-parser')
var awsServerlessExpressMiddleware = require('aws-serverless-express/middleware')

// declare a new express app
var app = express()
app.use(bodyParser.json())
app.use(awsServerlessExpressMiddleware.eventContext())

// Enable CORS for all methods
app.use(function(req, res, next) {
  res.header("Access-Control-Allow-Origin", "*")
  res.header("Access-Control-Allow-Headers", "*")
  next()
});


// Util Function 1 : 사용자가 현재 속해 있는 그룹 확인
const getGroupsForUser = async (event) => {
  // cognitoAuthenticationProvider returns...
  // cognito-idp. region.amazonaws.com/user_pool_id,cognito-idp.region.amazonaws.com/user_pool_id:CognitoSignIn:<token subject claim>
  // :CognitoSignIn: 뒷 부분에 유저 토큰
  let userSub = event.requestContext
    .identity
    .cognitoAuthenticationProvider
    .split(":CognitoSignIn:")[1];

    let userParams = {
      UserPoolId: userpoolId,
      Filter: `sub = "${userSub}"`,
    };

    // cognito api를 통해 유저 정보 획득
    let userData = await cognitoProvider.listUsers(userParams).promise();
    let user = userData.Users[0];

    let groupParams = {
      UserPoolId: userpoolId,
      Username: user.Username
    };

    // cognito api를 통해 해당 유저가 속한 그룹 리스트 획득
    // https://docs.aws.amazon.com/cognito-user-identity-pools/latest/APIReference/API_AdminListGroupsForUser.html
    const groupData = await cognitoProvider.adminListGroupsForUser(groupParams).promise();
    return groupData;
};

// Util Function 2 : group 파라미터를 통해 해당 그룹에 속해 있는 경우, event 인자 수행
const canPerformAction = async (event, group) => {
  return new Promise(async (resolve, reject) => {
    // 인증된 사용자가 아닌 경우(비로그인), 요청 거부
    if(!event.requestContext.identity.cognitoAuthenticationProvider) {
      return reject();
    }

    // 요청으로 들어온 사용자 정보를 통해 해당 사용자가 속한 그룹 리스트
    const groupData = await getGroupsForUser(event);
    const groupsForUser = groupData.Groups.map(g => g.GroupName);

    // Admin 그룹에 속한 경우만 액션 수행
    if (groupsForUser.includes(group)){
      resolve();
    } else {
      reject("user not in group, cannot perform action!");
    }

  })
};


/**********************
 * Example get method *
 **********************/

const getItems = async () => {
  let params = { TableName: db_table_name };

  try {
    const data = await db_client.scan(params).promise();
    return data;
  } catch(err) {
    return err;
  }
};

app.get('/products', async function(req, res) {
  try {
    const data = await getItems();
    res.json({
      data: data
    });
  } catch (e) {
    res.json({
      error: e
    });
  }
});

app.get('/products/*', function(req, res) {
  // Add your code here
  res.json({success: 'get call succeed!', url: req.url});
});

/****************************
* Example post method *
****************************/

app.post('/products', async function(req, res) {
  const { body } = req;
  const { event } = req.apiGateway;
  
  try{
    // 관리자만 사용 가능
    await canPerformAction(event, "Admin");

    // Table에 insert
    const input = {...body, id: uuid()};
    let params = {
      TableName: db_table_name,
      Item: input
    };
    await db_client.put(params).promise();

    res.json({
      success: "Success to save an item",
      item: input
    });
  } catch (e) {
    res.json({
      error: e
    });
  }
});

app.post('/products/*', function(req, res) {
  // Add your code here
  res.json({success: 'post call succeed!', url: req.url, body: req.body})
});

/****************************
* Example put method *
****************************/

app.put('/products', async function(req, res) {
  const { body } = req;
  const { event } = req.apiGateway;

  try {
    // 관리자만 사용 가능
    await canPerformAction(event, "Admin");

    var params = {
      TableName: db_table_name,
      Key: { id: body.id },
      UpdateExpression: "set price = :newprice, name = :newname",
      ExpressionAttributeValues: { 
        ":newprice": body.price,
        ":newname": body.name 
      }
    }
    await db_client.update(params).promise()
    res.json({ 
      success: "Success to update the item" 
    });
  } catch (e) {
    res.json({ 
      error: e 
    });
  }
});

app.put('/products/*',  function(req, res) {
  // Add your code here
  res.json({success: 'put call succeed!', url: req.url, body: req.body})
});

/****************************
* Example delete method *
****************************/

app.delete('/products', async function(req, res) {
  const { event } = req.apiGateway;
  try{
    // 관리자만 사용 가능
    await canPerformAction(event, "Admin");

    // Table에서 delete
    let params = {
      TableName: db_table_name,
      Key: { id: req.body.id }
    };
    await db_client.delete(params).promise();
    res.json({
      success: "Success to delete the item"
    });
  } catch (e) {
    res.json({
      error: e
    });
  }
});

app.delete('/products/*',  function(req, res) {
  // Add your code here
  res.json({success: 'delete call succeed!', url: req.url});
});

app.listen(3000, function() {
    console.log("App started")
});

// Export the app object. When executing the application local this does nothing. However,
// to port it to AWS Lambda we will create a wrapper around that will load the app from
// this file
module.exports = app
