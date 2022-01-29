package com.yj.search;

public interface SearchClientFactory {
    public void init();

    public SearchClient create();
}
