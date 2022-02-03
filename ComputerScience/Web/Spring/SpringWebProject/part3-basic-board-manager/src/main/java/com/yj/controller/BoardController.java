package com.yj.controller;

import com.yj.domain.BoardVO;
import com.yj.service.BoardService;
import lombok.Setter;
import lombok.extern.log4j.Log4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;

@Controller
@Log4j
@RequestMapping("/board/*")
public class BoardController {

    @Setter(onMethod_ = @Autowired)
    private BoardService service;

    @GetMapping("/list")
    public void list(Model model) {
        model.addAttribute("boardList", service.getList());
    }

    @GetMapping("/register")
    public void register() {}

    @PostMapping("/register")
    public String register(BoardVO board, RedirectAttributes redirectAttributes) {
        service.register(board);

        // 플래시 메시지 추가
        redirectAttributes.addFlashAttribute("flashMsg", board.getId());

        // 리스트로 리다이렉트
        return "redirect:/board/list";
    }

    @GetMapping({"/get", "modify"})
    public void getForm(@RequestParam("id") Long id, Model model) {
        model.addAttribute("board", service.getById(id));
    }

    @PostMapping("/modify")
    public String modify(BoardVO board, RedirectAttributes redirectAttributes) {
        String flashMessage = null;
        if (service.modify(board)) {
            flashMessage = "Success to Update";
        } else {
            flashMessage = "Fail to Update";
        }

        redirectAttributes.addFlashAttribute("flashMsg", flashMessage);
        return "redirect:/board/list";
    }

    @PostMapping("/remove")
    public String remove(@RequestParam("id") Long id, RedirectAttributes redirectAttributes) {
        String flashMessage = null;
        if (service.remove(id)) {
            flashMessage = "Success to Delete";
        } else {
            flashMessage = "Fail to Delete";
        }

        redirectAttributes.addFlashAttribute("flashMsg", flashMessage);
        return "redirect:/board/list";
    }
}
