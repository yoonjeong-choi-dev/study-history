package com.yj.search;

public class HttpSearchClient implements SearchClient {
    @Override
    public void addDocument(String docs) {
        System.out.println("Http Client : 문서 추가됨");
    }

    public void checkLive() {
        System.out.println("Http Client : 상태 확인");
    }
}
