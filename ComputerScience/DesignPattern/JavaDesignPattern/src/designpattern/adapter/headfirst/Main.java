package designpattern.adapter.headfirst;

import designpattern.adapter.headfirst.adaptee.*;
import designpattern.adapter.headfirst.Target.*;
import designpattern.adapter.headfirst.adapter.*;

import java.util.Iterator;
import java.util.Vector;

public class Main {
    public static void main(String[] args) {
        System.out.println("Duck - Turkey Simulation");
        exampleDuck2Turkey();
        System.out.println();

        System.out.println("Enumeration - Iterator Simulation");
        exampleEnumeration2Iterator();
        System.out.println();
    }

    private static void exampleDuck2Turkey() {
        // 기존에 제공되는 객체 생성
        Duck duck = new MallardDuck();

        Turkey turkey = new WildTurkey();
        Turkey duckAdapter = new DuckAdapter(duck);

        System.out.println("The turkey is doing...");
        doTurkey(turkey);

        System.out.println("The duck is doing...");
        doTurkey(duckAdapter);
    }

    private static void doTurkey(Turkey turkey) {
        turkey.gobble();
        turkey.fly();
    }

    private static void exampleEnumeration2Iterator() {
        // Enumeration 객체를 사용하는 대표적인 레거시 클래스인 Vector 이용
        Vector<Integer> vector = new Vector<>();
        vector.add(1);
        vector.add(111);
        vector.add(11);

        Iterator<Integer> iterator = new EnumerationIterator<>(vector.elements());
        while(iterator.hasNext()) {
            System.out.println(iterator.next());
        }
    }

}
