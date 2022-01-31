package com.yj.sample;

import lombok.extern.log4j.Log4j;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;

@Controller
@Log4j
public class SampleController {
    @GetMapping("/sample")
    public String sample() {
        log.info("=============================");
        log.info("SampleController Test");
        log.info("=============================");

        return "sample";
    }
}