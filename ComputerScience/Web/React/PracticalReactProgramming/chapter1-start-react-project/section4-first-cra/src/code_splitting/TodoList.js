import React, {useState} from 'react';
import { Todo } from './Todo';

const TodoList = () => {
    const [todos, setTodos] = useState([]);
    
    const onClick = () => {
        // 버튼을 클릭 시에 동적으로 Todo 모듈을 가져옴
        // 네트워크 탭에서 확인 가능
        import ('./Todo').then(({Todo}) => {
            const position = todos.length + 1;
            const newTodo = <Todo key={position} title={`할 일 ${position}`} />;
            setTodos([...todos, newTodo]);
        });
    };

    return (
        <div>
            <button onClick={onClick}>Add Todo</button>
            {todos}
        </div>
    );
};

export default TodoList;