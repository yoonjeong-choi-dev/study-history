package com.yj.controller;

import com.yj.domain.TodoDTO;
import lombok.extern.log4j.Log4j;
import org.springframework.beans.propertyeditors.CustomDateEditor;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.WebDataBinder;
import org.springframework.web.bind.annotation.*;

import java.awt.image.SampleModel;
import java.text.SimpleDateFormat;

@Controller
@RequestMapping("/binding/*")
@Log4j
public class BindingController {
    @InitBinder
    public void InitBinder(WebDataBinder binder) {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
        binder.registerCustomEditor(java.util.Date.class, new CustomDateEditor(dateFormat, false));
    }

    @GetMapping("/")
    public String getForm() {
        return "binding/form";
    }

    @PostMapping("/post")
    public  String getResult(TodoDTO dto, Model model){
        log.info(dto);
        model.addAttribute("todo", dto);
        return "binding/post";
    }

    @PostMapping("/postModelAttribute")
    public String getWithAttribute(TodoDTO dto, @ModelAttribute("page") int page, Model model) {
        log.info("dto : " + dto);
        log.info("page : " + page);

        model.addAttribute("todo", dto);
        return "/binding/postModelAttribute";
    }
}
