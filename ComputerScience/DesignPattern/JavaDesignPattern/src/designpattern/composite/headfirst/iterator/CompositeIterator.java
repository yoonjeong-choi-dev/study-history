package designpattern.composite.headfirst.iterator;

import designpattern.composite.headfirst.Menu;
import designpattern.composite.headfirst.MenuComponent;

import java.util.Iterator;
import java.util.Stack;
/**
 * Component 역할에 대한 이터레이터 패턴 적용
 */
public class CompositeIterator implements Iterator<MenuComponent> {

    private final Stack<Iterator<MenuComponent>> stack = new Stack<>();

    public CompositeIterator(Iterator<MenuComponent> iterator) {
        stack.push(iterator);
    }

    @Override
    public boolean hasNext() {
        if(stack.isEmpty()) return false;

        Iterator<MenuComponent> iterator = stack.peek();
        if(!iterator.hasNext()) {
            // 스택 top 이터레이터가 끝난 경우 스택에서 제거하고 다시 재귀 호출을 하여 남아 있는 컴포넌트까지 탐색
            stack.pop();
            return hasNext();
        } else {
            return true;
        }
    }

    @Override
    public MenuComponent next() {
        if(!hasNext()) {
            return  null;
        }

        // 현재 스택의 top에 존재하는 이터레이터에서 컴포넌트 가져오기
        Iterator<MenuComponent> iterator = stack.peek();
        MenuComponent component = iterator.next();

        // 컴포넌트가 복합체인 경우, 이터레이터를 스택에 추가 : 트리에 대한 dfs 탐색 형태
        if(component instanceof Menu) {
            stack.push(component.createIterator());
        }
        return component;
    }
}
