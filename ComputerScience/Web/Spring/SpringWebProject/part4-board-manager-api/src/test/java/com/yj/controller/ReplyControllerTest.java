package com.yj.controller;

import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.get;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.post;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.delete;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.put;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.status;
import static org.junit.jupiter.api.Assertions.assertEquals;


import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.TypeAdapter;
import com.google.gson.reflect.TypeToken;
import com.google.gson.stream.JsonReader;
import com.google.gson.stream.JsonWriter;

import com.yj.domain.ReplyPageDTO;
import lombok.Setter;
import lombok.extern.log4j.Log4j;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.mock.web.MockHttpServletResponse;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit.jupiter.SpringExtension;
import org.springframework.test.context.web.WebAppConfiguration;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.MvcResult;
import org.springframework.test.web.servlet.setup.MockMvcBuilders;
import org.springframework.web.context.WebApplicationContext;

import java.io.IOException;
import java.lang.reflect.Type;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.ArrayList;
import java.util.List;
import java.util.TimeZone;

import com.yj.domain.ReplyVO;

@ExtendWith(SpringExtension.class)
@WebAppConfiguration
@ContextConfiguration({
        "file:src/main/webapp/WEB-INF/spring/root-context.xml",
        "file:src/main/webapp/WEB-INF/spring/appServlet/servlet-context.xml"
})
@Log4j
public class ReplyControllerTest {

    static final String testDateFormat = "yyyy-MM-dd HH:mm:ss";
    static DateFormat format = new SimpleDateFormat(testDateFormat);
    static {
        format.setTimeZone(TimeZone.getTimeZone("Asia/Seoul"));
    }

    private static class TimestampTypeAdapter extends TypeAdapter<Date> {
        @Override
        public void write(JsonWriter out, Date value) throws IOException {
            if (value == null) {
                out.nullValue();
                return;
            }
            out.value(value.getTime() / 1000);
        }

        @Override
        public Date read(JsonReader in) throws IOException {
            if (in == null) {
                return null;
            }
            return new Date(in.nextLong() * 1000);
        }
    }

    final String baseUrl = "/replies/";
    static Gson gson = null;

    // 테스트를 위해 외래키 board_id 미리 지정
    private final Long[] boardIdArr = {1L, 2L, 4L, 8L, 9L};

    @Setter(onMethod_ = {@Autowired})
    private WebApplicationContext ctx;

    private MockMvc mockMvc;

    @BeforeAll
    static public void setupGson() {
        gson = new GsonBuilder().registerTypeAdapter(java.util.Date.class, new TimestampTypeAdapter()).setDateFormat(testDateFormat).create();
    }

    @BeforeEach
    public void setupMock() {
        mockMvc = MockMvcBuilders.webAppContextSetup(ctx).build();
    }

    @Test
    public void testRegister() throws Exception {
        ReplyVO vo = new ReplyVO();
        vo.setBoardId(boardIdArr[0]);
        vo.setReply("Register Test Revised");
        vo.setReplier("ControllerTest");

        String jsonStr = gson.toJson(vo);

        log.info("Register Test");
        mockMvc.perform(post(baseUrl + "register").contentType(MediaType.APPLICATION_JSON).content(jsonStr))
                .andExpect(status().is(200));
    }

    @Test
    void testPageList() throws Exception {
        MvcResult ret = mockMvc.perform(get(baseUrl + "pages/" + boardIdArr[0] + "/1.json")).andReturn();

        MockHttpServletResponse response = ret.getResponse();
        assertEquals(response.getStatus(), 200);

        String contents = response.getContentAsString();

//        Type type = new TypeToken<ArrayList<ReplyVO>>(){}.getType();
//        List<ReplyVO> replies = gson.fromJson(contents, type);
//
//        log.info("Test GET /pages");
//        log.info("Response Content : " + contents);
//        replies.forEach(reply -> log.info(reply));

        ReplyPageDTO dto = gson.fromJson(contents, ReplyPageDTO.class);
        log.info("Test GET /pages");
        log.info("Response Content : " + contents);
        log.info("Total Count : " + dto.getNumReplies());
        dto.getReplies().forEach(reply -> log.info(reply));
    }

    @Test
    void testGet() throws Exception {
        Long targetId = 12L;
        MvcResult ret = mockMvc.perform(get(baseUrl + targetId + ".json")).andReturn();

        MockHttpServletResponse response = ret.getResponse();
        assertEquals(response.getStatus(), 200);

        String contents = response.getContentAsString();
        log.info("Response Content : " + contents);
        ReplyVO reply = gson.fromJson(contents, ReplyVO.class);

        log.info("Test Get /{id}");
        log.info("Response Content : " + contents);
        log.info("VO : " + reply);
    }

    @Test
    void testDelete() throws Exception {
        Long targetId = 13L;
        MvcResult ret = mockMvc.perform(delete(baseUrl + targetId + ".json")).andReturn();

        MockHttpServletResponse response = ret.getResponse();
        assertEquals(response.getStatus(), 200);

        String contents = response.getContentAsString();

        log.info("Test Delete /{id}");
        log.info("Response Content : " + contents);
    }

    @Test
    void testUpdate() throws Exception {
        Long targetId = 15L;
        MvcResult ret = mockMvc.perform(get(baseUrl + targetId + ".json")).andReturn();

        MockHttpServletResponse response = ret.getResponse();
        String contents = response.getContentAsString();

        ReplyVO reply = gson.fromJson(contents, ReplyVO.class);
        reply.setReply("Controller Modify Test");

        String jsonStr = gson.toJson(reply);

        ret = mockMvc.perform(put(baseUrl + targetId  + " .json").contentType(MediaType.APPLICATION_JSON)
                .content(jsonStr)).andReturn();

        response = ret.getResponse();
        assertEquals(response.getStatus(), 200);

        contents = response.getContentAsString();

        log.info("Test Put /{id}");
        log.info("Response Content : " + contents);
    }
}
