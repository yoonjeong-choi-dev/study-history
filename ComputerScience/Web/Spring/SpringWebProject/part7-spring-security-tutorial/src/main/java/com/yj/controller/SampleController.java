package com.yj.controller;

import lombok.extern.log4j.Log4j;
import org.springframework.security.access.annotation.Secured;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@Log4j
@RequestMapping("/sample/*")
public class SampleController {
    @PreAuthorize("hasAnyRole('ROLE_ADMIN', 'ROLE_MEMBER')")
    @GetMapping("/preAuth")
    public void preAuthAnnotation() {
        log.info("[PreAuthorize] : Only member and admin");
    }

    @Secured({"ROLE_ADMIN"})
    @GetMapping("/secured")
    public void securedAnnotation() {
        log.info("[Secured] : Only admin");
    }
}
