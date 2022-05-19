package com.yj.controller;

import com.yj.domain.todo.TodoEntity;
import com.yj.dto.ResponseListDTO;
import com.yj.dto.todo.TodoDTO;
import com.yj.service.TodoService;
import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.security.core.annotation.AuthenticationPrincipal;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.List;

@RequiredArgsConstructor
@RestController
@RequestMapping("/todo")
public class TodoController {
    private final TodoService todoService;

    @GetMapping("/test")
    public ResponseEntity<?> test() {
        String str = todoService.test();

        List<String> body = new ArrayList<>();
        body.add(str);

        ResponseListDTO<String> responseListDTO = ResponseListDTO.<String>builder().data(body).error("SUCCESS").build();
        return ResponseEntity.ok(responseListDTO);
    }

    @GetMapping("/all")
    public ResponseEntity<?> getAll() {
        List<TodoEntity> entities = todoService.getAll();
        List<TodoDTO> responseBodies = entities.stream().map(TodoDTO::new).toList();

        ResponseListDTO<TodoDTO> response = ResponseListDTO.<TodoDTO>builder().data(responseBodies).build();
        return ResponseEntity.ok(response);
    }

    @GetMapping
    public ResponseEntity<?> getTodoList(@AuthenticationPrincipal String userId) {
        List<TodoEntity> entities = todoService.getResultByUserId(userId);
        List<TodoDTO> responseBodies = entities.stream().map(TodoDTO::new).toList();

        ResponseListDTO<TodoDTO> response = ResponseListDTO.<TodoDTO>builder().data(responseBodies).build();
        return ResponseEntity.ok(response);
    }

    @PostMapping
    public ResponseEntity<?> createTodo(@AuthenticationPrincipal String userId, @RequestBody TodoDTO dto) {
        try {
            TodoEntity todoEntity = TodoDTO.toEntity(dto);
            todoEntity.setId(null);
            todoEntity.setUserId(userId);

            // Service 레이어를 이용하여 저장
            List<TodoEntity> entities = todoService.create(todoEntity);
            List<TodoDTO> responseBodies = entities.stream().map(TodoDTO::new).toList();

            ResponseListDTO<TodoDTO> response = ResponseListDTO.<TodoDTO>builder().data(responseBodies).build();
            return ResponseEntity.ok(response);
        } catch (Exception e) {
            e.printStackTrace();
            String errorMessage = e.getMessage();
            ResponseListDTO<TodoDTO> response = ResponseListDTO.<TodoDTO>builder().error(errorMessage).build();
            return ResponseEntity.badRequest().body(response);
        }
    }

    @PutMapping
    public ResponseEntity<?> updateTodo(@AuthenticationPrincipal String userId, @RequestBody TodoDTO dto) {
        TodoEntity todoEntity = TodoDTO.toEntity(dto);
        todoEntity.setUserId(userId);

        // Service 레이어를 이용하여 업데이트
        List<TodoEntity> entities = todoService.update(todoEntity);
        List<TodoDTO> responseBodies = entities.stream().map(TodoDTO::new).toList();
        ResponseListDTO<TodoDTO> response = ResponseListDTO.<TodoDTO>builder().data(responseBodies).build();
        return ResponseEntity.ok(response);
    }

    @DeleteMapping
    public ResponseEntity<?> deleteTodo(@AuthenticationPrincipal String userId, @RequestBody TodoDTO dto) {
        try {
            TodoEntity todoEntity = TodoDTO.toEntity(dto);
            todoEntity.setUserId(userId);

            // Service 레이어를 이용하여 저장
            List<TodoEntity> entities = todoService.delete(todoEntity);
            List<TodoDTO> responseBodies = entities.stream().map(TodoDTO::new).toList();

            ResponseListDTO<TodoDTO> response = ResponseListDTO.<TodoDTO>builder().data(responseBodies).build();
            return ResponseEntity.ok(response);
        } catch (Exception e) {
            e.printStackTrace();
            String errorMessage = e.getMessage();
            ResponseListDTO<TodoDTO> response = ResponseListDTO.<TodoDTO>builder().error(errorMessage).build();
            return ResponseEntity.badRequest().body(response);
        }
    }
}
