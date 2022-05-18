package com.yj.dto.user;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Getter;
import lombok.NoArgsConstructor;

@NoArgsConstructor
@AllArgsConstructor
@Builder
@Getter
public class UserDTO {
    private String token;
    private String email;
    private String username;
    private String password;
    private String id;
}
