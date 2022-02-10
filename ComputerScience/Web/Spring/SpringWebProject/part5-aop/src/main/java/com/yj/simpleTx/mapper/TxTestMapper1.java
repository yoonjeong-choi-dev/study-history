package com.yj.simpleTx.mapper;

import org.apache.ibatis.annotations.Insert;

public interface TxTestMapper1 {
    @Insert("insert into tx_test1 (col1) values (#{data})")
    public int insert(String data);
}
