package com.yj.controller;

import lombok.extern.log4j.Log4j;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.multipart.MultipartFile;

import java.util.ArrayList;

@Controller
@RequestMapping("/upload/*")
@Log4j
public class UploadController {
    @GetMapping("/")
    public String getForm() {
        return "upload/form";
    }

    @PostMapping("/uploadFile")
    public String uploadFile(ArrayList<MultipartFile> files) {
        files.forEach(file -> {
            log.info("=========================");
            log.info("name : " + file.getName());
            log.info("size : " + file.getSize());
            log.info("content type : " + file.getContentType());
        });

        return "redirect:/upload/";
    }
}
