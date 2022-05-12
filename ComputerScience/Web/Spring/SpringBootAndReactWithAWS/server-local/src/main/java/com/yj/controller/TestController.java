package com.yj.controller;

import com.yj.dto.test.TestRequestDTO;
import org.springframework.web.bind.annotation.*;

import java.util.logging.Logger;

@RestController
@RequestMapping("/test")
public class TestController {

    private static final Logger logger = Logger.getLogger(TestController.class.getName());

    @GetMapping("/testGet")
    public String testGet() {
        return "Get Mapping with RESTContoller";
    }

    @GetMapping("/echo/{name}")
    public String echoGet(@PathVariable(required = false) String name) {
        logger.info(new Object() {}.getClass().getEnclosingMethod().getName() + " : " + name);
        return String.format("Hello ~ %s!", name);
    }

    @GetMapping("/echo")
    public String echoQueryParamGet(@RequestParam(required = false) String name) {
        logger.info(new Object() {}.getClass().getEnclosingMethod().getName() + " : " + name);
        if (name == null) {
            name = "anonymous";
        }
        return String.format("Hello ~ %s!", name);
    }

    @PostMapping("/requestBody")
    public String requestBodyGet(@RequestBody TestRequestDTO request) {
        logger.info(new Object() {}.getClass().getEnclosingMethod().getName());
        return String.format("Hello~ %s! Your age is %d", request.getName(), request.getAge());
    }
}
