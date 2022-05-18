package com.yj.controller;

import com.yj.domain.user.UserEntity;
import com.yj.dto.ResponseListDTO;
import com.yj.dto.ResponseSingleDTO;
import com.yj.dto.user.UserDTO;
import com.yj.security.TokenProvider;
import com.yj.service.UserService;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@Slf4j
@RequiredArgsConstructor
@RestController
@RequestMapping("/auth")
public class UserController {
    private final UserService userService;
    private final TokenProvider tokenProvider;

    @PostMapping("/signup")
    public ResponseEntity<?> register(@RequestBody UserDTO userDTO) {
        ResponseSingleDTO<UserDTO> response;
        try {
            UserEntity user = UserEntity.builder()
                    .email(userDTO.getEmail())
                    .username(userDTO.getUsername())
                    .password(userDTO.getPassword())
                    .build();

            UserEntity registeredUser = userService.createUser(user);

            UserDTO responseData = UserDTO.builder()
                    .email(registeredUser.getEmail())
                    .id(registeredUser.getId())
                    .username(registeredUser.getUsername())
                    .build();

            response = ResponseSingleDTO.<UserDTO>builder().data(responseData).build();
            return ResponseEntity.ok(response);
        } catch (Exception e) {
            response = ResponseSingleDTO.<UserDTO>builder().error(e.getMessage()).build();
            return ResponseEntity
                    .badRequest()
                    .body(response);
        }
    }

    @PostMapping("/signin")
    public ResponseEntity<?> authenticate(@RequestBody UserDTO userDTO) {
        ResponseSingleDTO<UserDTO> response;
        UserEntity user = userService.getByCredential(userDTO.getEmail(), userDTO.getPassword());

        if (user != null) {
            // 토큰 생성
            final String token = tokenProvider.create(user);
            final UserDTO responseData = UserDTO.builder()
                    .email(user.getEmail())
                    .id(user.getId())
                    .token(token)
                    .build();

            response = ResponseSingleDTO.<UserDTO>builder().data(responseData).build();
            return ResponseEntity.ok(response);
        } else {
            response = ResponseSingleDTO.<UserDTO>builder().error("Login Failed").build();
            return ResponseEntity
                    .badRequest()
                    .body(response);
        }
    }
}
