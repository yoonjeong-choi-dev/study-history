package com.yj.mapper;

import org.apache.ibatis.annotations.Select;

public interface TimeMapper {
    @Select("select sysdate()")
    public String getTime();

    public String getTimeWithXML();
}
