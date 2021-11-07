import React from "react";
import { render } from "react-dom";
import App from "./App";
import { ApolloProvider } from "react-apollo";
import ApolloClient, { gql, InMemoryCache } from "apollo-boost";
import { persistCache } from "apollo-cache-persist";

// 클라이언트 캐시 설정
// 로컬 스토리지에 캐시 저장
const cache = new InMemoryCache()
persistCache({
    cache,
    storage: localStorage
})

// 캐시가 존재하면, 클라이언트 객체 생성전 초기화
if(localStorage["apollo-cache-persist"]) {
    console.log("Apollo Cache Restore...");

    let cacheData = JSON.parse(localStorage["apollo-cache-persist"]);
    cache.resotre(cacheData);
}


// create Apollo client with the server api
// 요청마다 로컬 스토리지에 저장해둔 토큰을 헤더에 포함시킨다
const client = new ApolloClient({
    uri: "http://localhost:4000/graphql",
    request: operation => {
        operation.setContext(context => ({
            headers: {
                ...context.headers,
                authorization: localStorage.getItem('token')
            }
        }))
    }
});

// sample query and reqeust
const sample_test_code = () => {
    // sample query
    const query = gql`
        {
            totalUsers
            totalPhotos
        }
    `
    // cache
    console.log("init cache", client.extract());
    // sample request 
    client.query({query})
            .then(res => console.log(res))
            .then(() => console.log("cache after query", client.extract()))
            .catch(console.error);
}
//sample_test_code();


render(
    <ApolloProvider client={client}>
        <App />
    </ApolloProvider>,
    document.getElementById('root')
)