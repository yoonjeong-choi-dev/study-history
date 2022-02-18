package com.yj.domain;

import lombok.Data;

import java.util.Date;
import java.util.List;

@Data
public class MemberVO {
    private String userId;
    private String userPw;
    private String userName;
    private boolean enabled;

    private Date registeredDate;
    private Date modifiedDate;

    private List<AuthVO> authList;
}
