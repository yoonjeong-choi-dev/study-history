package com.yj.controller;

import lombok.Setter;
import lombok.extern.log4j.Log4j;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit.jupiter.SpringExtension;
import org.springframework.test.context.web.WebAppConfiguration;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.setup.MockMvcBuilders;
import org.springframework.ui.ModelMap;
import org.springframework.web.context.WebApplicationContext;
import org.springframework.web.servlet.ModelAndView;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;

@ExtendWith(SpringExtension.class)
@WebAppConfiguration
@ContextConfiguration({
        "file:src/main/webapp/WEB-INF/spring/root-context.xml",
        "file:src/main/webapp/WEB-INF/spring/appServlet/servlet-context.xml"
})
@Log4j
class BoardControllerTest {
    final String baseUrl = "/board";

    @Setter(onMethod_ = {@Autowired})
    private WebApplicationContext ctx;

    private MockMvc mockMvc;

    @BeforeEach
    public void setupMock() {
        mockMvc = MockMvcBuilders.webAppContextSetup(ctx).build();
    }


    @Test
    public void testList() throws Exception {
        ModelAndView ret = mockMvc.perform(MockMvcRequestBuilders.get(baseUrl + "/list")
                        .param("pageNum", "3")
                        .param("numContents", "5"))
                .andReturn().getModelAndView();
        assertNotNull(ret);

        ModelMap modelMap = ret.getModelMap();

        log.info("Test GET /list");
        modelMap.forEach((key, val) -> log.info(key + " : " + val));
    }

    @Test
    public void testRegister() throws Exception {
        ModelAndView ret = mockMvc.perform(MockMvcRequestBuilders.post(baseUrl + "/register")
                        .param("title", "Controller POST Test")
                        .param("content", "Controller Register Test")
                        .param("writer", "YJ-Controller-Test"))
                .andReturn().getModelAndView();
        assertNotNull(ret);

        String resultPage = ret.getViewName();
        assertEquals(resultPage, "redirect:/board/list");

        log.info("Test POST /register");
        log.info(resultPage);
    }

    @Test
    public void testGet() throws Exception {
        ModelAndView ret = mockMvc.perform(MockMvcRequestBuilders.get(baseUrl + "/get")
                        .param("id", "2"))
                .andReturn().getModelAndView();
        assertNotNull(ret);

        log.info("Test GET : /get");
        log.info(ret.getModelMap());
    }

    @Test
    void testModify() throws Exception {
        ModelAndView ret = mockMvc.perform(MockMvcRequestBuilders.post(baseUrl + "/modify")
                        .param("id", "5")
                        .param("title", "Controller Update POST Test")
                        .param("content", "Controller Modify Test")
                        .param("writer", "YJ-Controller-Test"))
                .andReturn().getModelAndView();
        assertNotNull(ret);

        String resultPage = ret.getViewName();
        assertEquals(resultPage, "redirect:/board/list");

        log.info("Test POST /modify");
        log.info(resultPage);
    }

    @Test
    void testRemove() throws Exception {
        ModelAndView ret = mockMvc.perform(MockMvcRequestBuilders.post(baseUrl + "/remove")
                        .param("id", "6"))
                .andReturn().getModelAndView();
        assertNotNull(ret);

        String resultPage = ret.getViewName();
        assertEquals(resultPage, "redirect:/board/list");

        log.info("Test POST /remove");
        log.info(resultPage);
    }
}
