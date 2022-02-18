package com.yj.controller;

import com.yj.domain.PageCriteria;
import com.yj.domain.ReplyPageDTO;
import com.yj.domain.ReplyVO;
import com.yj.service.ReplyService;
import lombok.Setter;
import lombok.extern.log4j.Log4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.web.bind.annotation.*;


@RequestMapping("/replies")
@RestController
@Log4j
public class ReplyController {
    @Setter(onMethod_ = @Autowired)
    private ReplyService service;

    @PreAuthorize("isAuthenticated()")
    @PostMapping(value = "/register", consumes = "application/json", produces = {MediaType.TEXT_PLAIN_VALUE})
    public ResponseEntity<String> register(@RequestBody ReplyVO reply) {
        int insertCount = service.register(reply);

        return insertCount == 1 ?
                new ResponseEntity<>("success", HttpStatus.OK)
                : new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
    }

    @GetMapping(value = "/pages/{id}/{page}", produces = {
            MediaType.APPLICATION_XML_VALUE,
            MediaType.APPLICATION_JSON_UTF8_VALUE})
    public ResponseEntity<ReplyPageDTO> getList(
            @PathVariable("id") Long boardId,
            @PathVariable("page") int page) {

        PageCriteria cri = new PageCriteria(page, 10);

        return new ResponseEntity<>(service.getList(cri, boardId), HttpStatus.OK);
    }

    @GetMapping(value = "/{id}", produces = {
            MediaType.APPLICATION_XML_VALUE,
            MediaType.APPLICATION_JSON_UTF8_VALUE})
    public ResponseEntity<ReplyVO> get(@PathVariable("id") Long id) {
        return new ResponseEntity<>(service.getById(id), HttpStatus.OK);
    }

    @PreAuthorize("principal.username == #reply.replier")
    @DeleteMapping(value = "/{id}", produces = {
            MediaType.APPLICATION_XML_VALUE,
            MediaType.APPLICATION_JSON_UTF8_VALUE})
    public ResponseEntity<String> remove(@RequestBody ReplyVO reply, @PathVariable("id") Long id) {
        return service.remove(id)
                ? new ResponseEntity<>("success", HttpStatus.OK)
                : new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
    }

    @PreAuthorize("principal.username == #reply.replier")
    @RequestMapping(method = {RequestMethod.PATCH, RequestMethod.PUT},
            value = "/{id}",
            produces = {
                    MediaType.APPLICATION_XML_VALUE,
                    MediaType.APPLICATION_JSON_UTF8_VALUE})
    public ResponseEntity<String> modify(@RequestBody ReplyVO reply, @PathVariable("id") Long id) {
        reply.setId(id);

        return service.modify(reply)
                ? new ResponseEntity<>("success", HttpStatus.OK)
                : new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
    }

}
