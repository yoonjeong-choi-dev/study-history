package designpattern.composite.headfirst;

import java.util.Iterator;

/**
 * Client 역할
 */
public class Waitress {
    // 컴포지트 패턴에 나오는 트리의 루트 노드 역할
    MenuComponent totalMenus;

    public Waitress(MenuComponent totalMenus) {
        this.totalMenus = totalMenus;
    }

    public void print() {
        totalMenus.print();
    }

    public void printVegetarian() {
        System.out.println("\n\n=================================");
        System.out.println("Vegetarian Menu");

        Iterator<MenuComponent> itr = totalMenus.createIterator();
        while (itr.hasNext()) {
            MenuComponent component = itr.next();

            // 컴포지트 패턴 자체가 Composite 인터페이스에 두 가지 역할(계층 구조 관리, 작업 처리) 부여
            // => 두 요소를 동일시 하기 위하여 단일 책임 원칙을 위배함
            // => 두 요소를 동일시 하기 위해서 instanceof 대신 try-catch 구문으로 MenuItem 객체에 대해서만 isVegetarian 메서드 호출
            try {
                if (component.isVegetarian()) {
                    component.print();
                }
            } catch (UnsupportedOperationException e) {
            }
        }

        System.out.println("=================================");
    }
}
