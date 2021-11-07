import React from "react";
import { render } from "react-dom";
import App from "./App";
import { ApolloProvider } from "react-apollo";
import { 
    InMemoryCache, 
    ApolloLink,
    ApolloClient,
    split,
    gql
} from "apollo-boost";
import { persistCache } from "apollo-cache-persist";
import { WebSocketLink } from "apollo-link-ws";
import { getMainDefinition } from "apollo-utilities";
import { createUploadLink } from "apollo-upload-client";

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
    cache.restore(cacheData);
}

// HTTP 요청을 위한 링크 : multipart/form-data 지원
const httpLink = createUploadLink({ uri: "http://localhost:4000/graphql" });

// 웹소켓을 위한 링크
const wsLink = new WebSocketLink({
    uri: "ws://localhost:4000/subscriptions",
    options: { reconnect: true}
});


// 요청마다 로컬 스토리지에 저장해둔 토큰을 헤더에 포함시켜 포워딩하는 링크
const authLink = new ApolloLink((operation, forward) => {
    operation.setContext(context => ({
        headers: {
            ...context.headers,
            authorization: localStorage.getItem("token")
        }
    }))
    return forward(operation)
})
const httpAuthLink = authLink.concat(httpLink);


// 요청이 서브스크립션이면 wsLink로, 다른 요청이면 httpAuthLink로 보내는 링크
const link = split(
    ({ query }) => {
        const { kind, operation } = getMainDefinition(query);
        return kind === "OperationDefinition" && operation === "subscription";
    }, 
    wsLink,
    httpAuthLink
)

// 링크와 캐시를 이용하여 아폴로 클라이언트 객체 생성
const client = new ApolloClient ({
    cache,
    link
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
    document.getElementById("root")
)