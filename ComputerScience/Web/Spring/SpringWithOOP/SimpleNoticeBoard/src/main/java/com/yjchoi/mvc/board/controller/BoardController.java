package com.yjchoi.mvc.board.controller;

import javax.validation.Valid;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.SessionAttributes;
import org.springframework.web.bind.support.SessionStatus;

import com.yjchoi.mvc.board.domain.BoardVO;
import com.yjchoi.mvc.board.service.BoardService;

@Controller
@SessionAttributes("boardVO")
public class BoardController {
	@Autowired
	private BoardService boardService;

	@RequestMapping(value = "/board/list")
	public String list(Model model) {
		model.addAttribute("boardList", boardService.list());
		return "/board/list";
	}

	@RequestMapping(value = "/board/read/{seq}")
	public String read(Model model, @PathVariable int seq) {
		model.addAttribute("boardVO", boardService.read(seq));
		return "/board/read";
	}

	// 게시글 쓰기
	@RequestMapping(value = "/board/write", method = RequestMethod.GET)
	public String write(Model model) {
		model.addAttribute("boardVO", new BoardVO());
		return "/board/write";
	}

	@RequestMapping(value = "/board/write", method = RequestMethod.POST)
	public String write(@Valid BoardVO boardVO, BindingResult bindingResult, SessionStatus sessionStatus) {
		if (bindingResult.hasErrors()) {
			return "/board/write";
		} else {
			boardService.write(boardVO);
			sessionStatus.setComplete(); // 세션 종료
			return "redirect:/board/list";
		}
	}

	// 게시글 수정 : 이미 세션에 VO가 저장되어 있음(GET을 통해 접속하기 때문에)
	@RequestMapping(value = "/board/edit", method = RequestMethod.GET)
	public String edit(@ModelAttribute BoardVO boardVO) {
		// @ModelAttribute이 붙은 객체는 자동으로 모델에 추가됨 : 객체 이름을 필드 값으로 갖는다
		return "/board/edit";
	}

	@RequestMapping(value = "/board/edit", method = RequestMethod.POST)
	public String edit(@Valid @ModelAttribute BoardVO boardVO, BindingResult result, SessionStatus sessionStatus,
			int pwd, Model model) {
		if (result.hasErrors()) {
			return "board/edit";
		} else {
			// 비밀번호 검증
			if (boardVO.getPassword() == pwd) {
				boardService.edit(boardVO);
				sessionStatus.setComplete(); // 세션 종료
				return "redirect:/board/list";
			} else {
				model.addAttribute("msg", "비밀번호가 일치하지 않습니다");
				return "/board/edit";
			}
		}
	}

	 //게시글 삭제
	 @RequestMapping(value="/board/delete/{seq}", method=RequestMethod.GET)
	 public String delete(@PathVariable int seq, Model model) {
	 model.addAttribute("seq", seq);
	 return "/board/delete";
	 }


	@RequestMapping(value = "/board/delete", method = RequestMethod.POST)
	public String delete(int seq, int pwd, Model model) {
		int rowCount;
		BoardVO boardVO = new BoardVO();

		// sqlmap-board.xml의 delete를 보면 seq과 비밀번호가 일치하는 데이터를 삭제함
		boardVO.setSeq(seq);
		boardVO.setPassword(pwd);

		rowCount = boardService.delete(boardVO);

		// 실패하는 경우
		if (rowCount == 0) {
			model.addAttribute("seq", seq);
			model.addAttribute("msg", "비밀번호가 일치하지 않습니다");
			return "/board/delete";
		} else {
			return "redirect:/board/list";
		}
	}
}
