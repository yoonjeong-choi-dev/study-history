package com.yj.controller;

import com.yj.domain.BoardAttachFileVO;
import com.yj.domain.BoardVO;
import com.yj.domain.PageCriteria;
import com.yj.domain.PageDTO;
import com.yj.service.BoardService;
import lombok.Setter;
import lombok.extern.log4j.Log4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;

@Controller
@Log4j
@RequestMapping("/board/*")
public class BoardController {

    @Setter(onMethod_ = @Autowired)
    private BoardService service;

    @GetMapping
    public void list(PageCriteria cri, Model model) {
        int totalCount = service.getTotalCount(cri);

        // 현재 페이지에 대한 파라미터 검증
        if (cri.getNumContents() * cri.getPageNum() > totalCount) {
            int maxPageNum = (int) Math.ceil((double) totalCount / (double) cri.getNumContents());
            cri.setPageNum(maxPageNum == 0 ? 1 : maxPageNum);
        }

        model.addAttribute("boardList", service.getList(cri));
        model.addAttribute("pageMaker", new PageDTO(cri, totalCount));
    }

    @GetMapping("/register")
    @PreAuthorize("isAuthenticated()")
    public void register() {
    }

    @PreAuthorize("isAuthenticated()")
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

    @PreAuthorize("principal.username == #board.writer")
    @PostMapping("/modify")
    public String modify(BoardVO board, @ModelAttribute("cri") PageCriteria cri, RedirectAttributes redirectAttributes) {
        String flashMessage = null;
        if (service.modify(board)) {
            flashMessage = "Success to Update";
        } else {
            flashMessage = "Fail to Update";
        }

        redirectAttributes.addFlashAttribute("flashMsg", flashMessage);
        return "redirect:/board/list" + cri.getListLink();
    }

    @PreAuthorize("principal.username == #writer")
    @PostMapping("/remove")
    public String remove(@RequestParam("id") Long id, @ModelAttribute("cri") PageCriteria cri, RedirectAttributes redirectAttributes,
                         String writer) {
        // 삭제할 첨부파일 데이터
        List<BoardAttachFileVO> files = service.getAttachList(id);
        String flashMessage = null;
        if (service.remove(id)) {
            deleteFiles(files);
            flashMessage = "Success to Delete";
        } else {
            flashMessage = "Fail to Delete";
        }

        redirectAttributes.addFlashAttribute("flashMsg", flashMessage);
        return "redirect:/board/list" + cri.getListLink();
    }

    private void deleteFiles(List<BoardAttachFileVO> files) {
        if (files == null || files.size() == 0) {
            return;
        }

        files.forEach(file -> {
            try {
                Path path = Paths.get(UploadController.getUploadPath() + "/" + file.getUploadPath() + "/" + file.getUuid()
                        + "_" + file.getFileName());
                boolean ret = Files.deleteIfExists(path);

                // 이미지의 경우 섬네일 제거
                if (file.getIsImage() == 1) {
                    Path thumbnail = Paths.get(UploadController.getUploadPath() + "/" + file.getUploadPath() + "/s_" + file.getUuid()
                            + "_" + file.getFileName());
                    Files.deleteIfExists(thumbnail);
                }

            } catch (IOException e) {
                e.printStackTrace();
            }
        });
    }

    @GetMapping(value = "/getAttachList", produces = MediaType.APPLICATION_JSON_UTF8_VALUE)
    @ResponseBody
    public ResponseEntity<List<BoardAttachFileVO>> getAttachList(Long boardId) {
        return new ResponseEntity<>(service.getAttachList(boardId), HttpStatus.OK);
    }
}
