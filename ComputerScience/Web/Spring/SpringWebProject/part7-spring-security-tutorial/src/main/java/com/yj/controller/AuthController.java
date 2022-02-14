package com.yj.controller;

import lombok.extern.log4j.Log4j;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;

@Log4j
@RequestMapping("/auth/*")
@Controller
public class AuthController {

    @GetMapping("/all")
    public void doForAll() {
        log.info("This is for All");
    }

    @GetMapping("/member")
    public void doForMember() {
        log.info("This is for only member");
    }

    @GetMapping("/admin")
    public void doForAdmin() {
        log.info("This is for only admin");
    }
}
