package com.yj.controller;

import com.yj.domain.BoardVO;
import com.yj.domain.PageCriteria;
import com.yj.domain.PageDTO;
import com.yj.service.BoardService;
import lombok.Setter;
import lombok.extern.log4j.Log4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;

@Controller
@Log4j
@RequestMapping("/board/*")
public class BoardController {

    @Setter(onMethod_ = @Autowired)
    private BoardService service;

//    @GetMapping("/list")
//    public void list(Model model) {
//        model.addAttribute("boardList", service.getList());
//    }

    @GetMapping
    public void list(PageCriteria cri, Model model) {
        int totalCount = service.getTotalCount(cri);

        // 현재 페이지에 대한 파라미터 검증
        if (cri.getNumContents() * cri.getPageNum() > totalCount ) {
            int maxPageNum = (int) Math.ceil((double) totalCount / (double) cri.getNumContents());
            cri.setPageNum(maxPageNum == 0? 1 : maxPageNum);
        }

        model.addAttribute("boardList", service.getList(cri));
        model.addAttribute("pageMaker", new PageDTO(cri, totalCount));
    }

    @GetMapping("/register")
    public void register() {}

    @PostMapping("/register")
    public String register(BoardVO board, RedirectAttributes redirectAttributes) {
        service.register(board);

        // 플래시 메시지 추가
        redirectAttributes.addFlashAttribute("flashMsg", "게시글 " + board.getId() + " 번이 등록되었습니다.");

        // 리스트로 리다이렉트
        return "redirect:/board/list";
    }

    @GetMapping({"/get", "modify"})
    public void getForm(@RequestParam("id") Long id, @ModelAttribute("cri") PageCriteria cri, Model model) {
        model.addAttribute("board", service.getById(id));
    }

    @PostMapping("/modify")
    public String modify(BoardVO board, @ModelAttribute("cri") PageCriteria cri, RedirectAttributes redirectAttributes) {
        String flashMessage = null;
        if (service.modify(board)) {
            flashMessage = "Success to Update";
        } else {
            flashMessage = "Fail to Update";
        }

        redirectAttributes.addFlashAttribute("flashMsg", flashMessage);
//        redirectAttributes.addAttribute("pageNum", cri.getPageNum());
//        redirectAttributes.addAttribute("numContents", cri.getNumContents());
//        redirectAttributes.addAttribute("type", cri.getType());
//        redirectAttributes.addAttribute("keyword", cri.getKeyword());
        return "redirect:/board/list" + cri.getListLink();
    }

    @PostMapping("/remove")
    public String remove(@RequestParam("id") Long id, @ModelAttribute("cri") PageCriteria cri, RedirectAttributes redirectAttributes) {
        String flashMessage = null;
        if (service.remove(id)) {
            flashMessage = "Success to Delete";
        } else {
            flashMessage = "Fail to Delete";
        }

        redirectAttributes.addFlashAttribute("flashMsg", flashMessage);
//        redirectAttributes.addAttribute("pageNum", cri.getPageNum());
//        redirectAttributes.addAttribute("numContents", cri.getNumContents());
//        redirectAttributes.addAttribute("type", cri.getType());
//        redirectAttributes.addAttribute("keyword", cri.getKeyword());
        return "redirect:/board/list" + cri.getListLink();
    }
}
