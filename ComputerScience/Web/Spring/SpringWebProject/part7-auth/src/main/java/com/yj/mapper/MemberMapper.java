package com.yj.mapper;

import com.yj.domain.MemberVO;

public interface MemberMapper {
    public MemberVO read(String userId);
}
