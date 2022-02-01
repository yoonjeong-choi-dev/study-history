package com.yj.settings;

import lombok.extern.log4j.Log4j;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@Log4j
public class TestController {
    @GetMapping("/test")
    public String getTestPage() {
        return "sample";
    }
}
