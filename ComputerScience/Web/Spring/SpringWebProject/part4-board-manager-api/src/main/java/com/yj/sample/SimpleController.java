package com.yj.sample;


import lombok.extern.log4j.Log4j;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

@RestController
@RequestMapping("/sample")
@Log4j
public class SimpleController {

    @GetMapping(value= "/getText", produces ="text/plain; charset=utf-8")
    public String getText() {
        return "Mime Type : "  + MediaType.TEXT_PLAIN_VALUE;
    }

    @GetMapping(value="/getSample", produces = {MediaType.APPLICATION_JSON_VALUE, MediaType.APPLICATION_XML_VALUE})
    public SampleVO getSample() {
        return new SampleVO(1, "Response with Object", "This is an object of a class");
    }

    @GetMapping(value = "/getList")
    public List<SampleVO> getList() {
        return IntStream.range(1, 10).mapToObj(i ->
                new SampleVO(i, "Response " + i, "Contents " + i))
                .collect(Collectors.toList());
    }

    @GetMapping(value = "getMap")
    public Map<String, SampleVO> getMam() {
        Map<String, SampleVO> map = new HashMap<>();
        map.put("First", new SampleVO(1, "Response with Map", "Map contents"));

        return map;
    }

    @GetMapping(value = "/check", params = {"height", "weight"})
    public ResponseEntity<SampleVO> check(Double height, Double weight) {
        SampleVO vo = new SampleVO();
        vo.setId(1);
        vo.setTitle("With HTTP Response");

        ResponseEntity<SampleVO> result;
        if (height < 150) {
            vo.setContents("Bad Request : Check the height param");
            result = ResponseEntity.status(HttpStatus.BAD_REQUEST).body(vo);
        } else {
            vo.setContents("Good Response : " + "(height, weight)=(" + height + ", " + weight + ")");
            result = ResponseEntity.status(HttpStatus.OK).body(vo);
        }
        return result;
    }

    @GetMapping(value = "/product/{cat}/{pid}")
    public String[] getPath(
            @PathVariable("cat") String category,
            @PathVariable("pid") Integer id ) {

        return new String[] {"category : " + category, "pid : " + id};
    }

    @PostMapping("/ticket")
    public Ticket convert(@RequestBody Ticket ticket) {
        ticket.setGrade(ticket.getGrade() + " SUCCESS!");
        return ticket;
    }
}
