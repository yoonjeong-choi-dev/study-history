package com.yj.dto.todo;

import com.yj.domain.todo.TodoEntity;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;

@NoArgsConstructor
@AllArgsConstructor
@Getter
public class TodoDTO {
    private String id;
    private String title;
    private boolean done;

    public TodoDTO(TodoEntity entity) {
        id = entity.getId();
        title = entity.getTitle();
        done = entity.isDone();
    }

    public static TodoEntity toEntity(final TodoDTO dto) {
        return TodoEntity.builder()
                .id(dto.getId())
                .title(dto.getTitle())
                .done(dto.isDone())
                .build();
    }
}
