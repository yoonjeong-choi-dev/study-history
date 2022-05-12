package com.yj.domain.todo;

import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;

import java.util.logging.Logger;

import static org.junit.jupiter.api.Assertions.*;

@SpringBootTest
@AutoConfigureMockMvc
class TodoRepositoryTest {

    private static final Logger logger = Logger.getLogger(TodoRepositoryTest.class.getName());

    @Autowired
    TodoRepository todoRepository;

    @Test
    public void insertTest() {
        TodoEntity entity = TodoEntity.builder().title("Insert Test").build();
        todoRepository.save(entity);

        TodoEntity savedEntity = todoRepository.findById(entity.getId()).orElse(null);
        assertNotNull(savedEntity);
        assertEquals(entity.getTitle(), savedEntity.getTitle());

        logger.info(savedEntity.getId());
    }
}