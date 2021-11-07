const fetch = require("node-fetch");
const fs = require("fs");

const findBy = (value, array, field="id") => array[array.map(item => item[field]).indexOf(value)];


// (client_id, client_secret, code)를 이용하여 GitHub에 엑세스 토큰 요청
const requestGithubToken = (credential) => {
    return fetch(
        "https://github.com/login/oauth/access_token",
        {
            method: "POST",
            headers: {
                "Content-Type": "application/json",
                Accept: "application/json"
            },
            body: JSON.stringify(credential)
        }
    ).then(res => res.json());
}


// 엑세스 토큰을 이용하여 사용자 계정 정보 접근
const requestGithubUserAccount = (token) => {
    return fetch(
        "https://api.github.com/user",
        {
            method: "GET",
            headers: {
                "Authorization": "token " + token
            }
        }
    )
    .then(res => res.json())
    .catch(error => {
        console.error("Fetch Error : ", error);
        throw new Error(error);
    });
} 
    
// (client_id, client_secret, code)를 이용하여 토큰 발행 및 사용자 정보 반환
const authorizeWithGithub = async (credentials) => {
    const { access_token } = await requestGithubToken(credentials);
    const githubUser = await requestGithubUserAccount(access_token);
    return { ...githubUser, access_token };
}

const uploadStream = (stream, path) => 
    new Promise( (resolve, reject) => {
        stream.on('error', error => {
            if (stream.truncated) {
                fs.unlinkSync(path)
            }
            reject(error)
        }).on('end', resolve)
        .pipe(fs.createWriteStream(path))
    })

const uploadFile = async (file, path) => {
    const { stream } = await file
    return uploadStream(stream, path)
}

module.exports = {findBy, authorizeWithGithub, uploadStream, uploadFile}