import { API_BASE } from "../config/config";

const ACCESS_TOEKN_LOCAL_STORAGE_KEY = 'ACCESS_TOKEN';

export function callAPI(apiResource, method, reqBody) {

  let headers = new Headers({
    'Content-Type': 'application/json',
  });

  // API 호출을 위한 토큰을 로컬 스토리지에서 가져오기
  const token = localStorage.getItem(ACCESS_TOEKN_LOCAL_STORAGE_KEY);

  // 토큰을 헤더에 추가
  if(token && token !== null) {
    headers.append('Authorization', 'Bearer ' + token);
  }

  let options = {
    headers,
    url: API_BASE + apiResource,
    method: method
  };

  if (reqBody) {
    options.body = JSON.stringify(reqBody);
  }

  return fetch(options.url, options)
    .then((res) =>
      res.json().then((json) => {
        if (!res.ok) {
          return Promise.reject(json);
        }
        return json;
      })
    )
    .catch((error) => {
      console.log(error.status);
      if (error.status === 403) {
        window.location.href = '/login';
      } else {
        console.error(error);
      }
      return Promise.reject(error);
    });
};

export function signin(user) {
  return callAPI('/auth/signin', 'POST', user)
    .then((res) => {
      console.log("response : " + JSON.stringify(res));

      // 로컬 스토리지(브라우저 스토리지)에 토큰 저장 => 이후 토큰이 유효한 경우, 로그인 과정 필요 X
      localStorage.setItem(ACCESS_TOEKN_LOCAL_STORAGE_KEY, res.data.token);
      //alert('Token : ' + res.data.token);

      // 로그인 성공 시, 메인 페이지로 리다이렉트
      window.location.href='/';
    })
};

export function signout() {
  localStorage.setItem(ACCESS_TOEKN_LOCAL_STORAGE_KEY, null);
  window.location.href='/login';
}

export function signup(user) {
  return callAPI('/auth/signup', 'POST', user);
}

export function isLogin() {
  // 로컬 스토리지에서 로그인 정보 가져오기
  const token = localStorage.getItem(ACCESS_TOEKN_LOCAL_STORAGE_KEY);

  // 로그인 정보가 있으면 true, 없으면 false
  if(token && token !== null) {
    return true;
  } else {
    return false;
  }
}