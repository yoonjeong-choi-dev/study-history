import { API_BASE } from "../config/config";

export function callAPI(apiResource, method, reqBody) {
  let options = {
    headers: new Headers({
      'Content-Type': 'application/json',
    }),
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
      console.error(error);
      return Promise.reject(error);
    });
}