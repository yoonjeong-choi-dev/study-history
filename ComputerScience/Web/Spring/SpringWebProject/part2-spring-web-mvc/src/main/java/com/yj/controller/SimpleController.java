package com.yj.controller;

import com.yj.domain.SimpleDTO;
import lombok.extern.log4j.Log4j;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

import java.util.ArrayList;

@Controller
@RequestMapping("/simple/*")
@Log4j
public class SimpleController {
    @GetMapping("")
    public String basic() {
        log.info("SimpleController.basic() : /simple url");
        return "simple/simple";
    }

    @GetMapping("/paramDto")
    public String dtoTest(SimpleDTO dto, Model model) {
        log.info("Dto Params : " + dto);

        model.addAttribute("name", dto.getName());
        model.addAttribute("age", dto.getAge());
        return "simple/paramDto";
    }

    @GetMapping("/paramList")
    public String listTest(@RequestParam("ids")ArrayList<String> ids, Model model) {
        log.info("Param List : " + ids);
        model.addAttribute("params", ids);
        return "simple/paramList";
    }

    @GetMapping("/json")
    public @ResponseBody SimpleDTO sendJSON() {
        SimpleDTO ret = new SimpleDTO();
        ret.setName("Choi Yoonjeong");
        ret.setAge(30);
        return ret;
    }
}
