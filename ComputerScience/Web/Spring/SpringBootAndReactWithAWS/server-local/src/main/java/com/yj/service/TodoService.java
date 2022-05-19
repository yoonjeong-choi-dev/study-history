package com.yj.service;

import com.yj.domain.todo.TodoEntity;
import com.yj.domain.todo.TodoRepository;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@RequiredArgsConstructor
@Slf4j
@Service
public class TodoService {

    private final TodoRepository todoRepository;

    public String test() {
        return "Test Service";
    }

    public List<TodoEntity> getAll() {
        return todoRepository.findAll();
    }

    public List<TodoEntity> create(final TodoEntity todoEntity) {
        // Step 1 : Validation
        validate(todoEntity);

        // Step 2 : Save into the database
        todoRepository.save(todoEntity);
        log.info("Saved Entity Id : {}", todoEntity.getId());

        return getResultByUserId(todoEntity.getUserId());
    }

    public List<TodoEntity> update(final TodoEntity todoEntity) {
        // Step 1 : Validation
        validate(todoEntity);

        // Step 2 : Id 를 이용하여 변경할 데이터가 있는지 확인
        final Optional<TodoEntity> original = todoRepository.findById(todoEntity.getId());
        original.ifPresent(todo -> {
            todo.setTitle(todoEntity.getTitle());
            todo.setDone(todoEntity.isDone());

            todoRepository.save(todo);
        });

        return getResultByUserId(todoEntity.getUserId());
    }

    public List<TodoEntity> delete(final TodoEntity todoEntity) {
        // Step 1 : Validation
        validate(todoEntity);

        try {
            todoRepository.delete(todoEntity);
        } catch (Exception e) {
            log.error("Error when deleting entity {} : {}", todoEntity.getId(), e);
            throw new RuntimeException("Error to delete the entity with id : " + todoEntity.getId());
        }

        return getResultByUserId(todoEntity.getUserId());
    }


    public List<TodoEntity> getResultByUserId(String userId) {
        return todoRepository.findByUserId(userId);
    }

    private void validate(final TodoEntity todoEntity) {
        if (todoEntity == null) {
            log.warn("Todo Entity is null");
            throw new RuntimeException("Entity cannot be null");
        }

        if (todoEntity.getUserId() == null) {
            log.warn("Todo Entity User id is null");

            throw new RuntimeException("Unknown User");
        }
    }
}
