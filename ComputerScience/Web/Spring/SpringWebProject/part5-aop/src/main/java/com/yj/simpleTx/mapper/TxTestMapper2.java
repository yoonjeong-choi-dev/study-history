package com.yj.simpleTx.mapper;

import org.apache.ibatis.annotations.Insert;

public interface TxTestMapper2 {
    @Insert("insert into tx_test2 (col2) values (#{data})")
    public int insert(String data);
}
