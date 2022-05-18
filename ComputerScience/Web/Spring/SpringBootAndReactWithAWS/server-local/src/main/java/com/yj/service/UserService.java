package com.yj.service;

import com.yj.domain.user.UserEntity;
import com.yj.domain.user.UserRepository;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;

@RequiredArgsConstructor
@Slf4j
@Service
public class UserService {

    private final UserRepository userRepository;

    public UserEntity createUser(final UserEntity userEntity) {
        if (userEntity == null || userEntity.getEmail() == null) {
            log.warn("Invalid Argument : entity is null or email is null");
            throw new RuntimeException("Invalid Argument");
        }

        final String email = userEntity.getEmail();
        if (userRepository.existsByEmail(email)) {
            log.warn("Email already exists : {}", email);
            throw new RuntimeException("Email already exists");
        }

        return userRepository.save(userEntity);
    }

    public UserEntity getByCredential(final String email, final String password) {
        return userRepository.findByEmailAndPassword(email, password);
    }
}
