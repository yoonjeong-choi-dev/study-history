package designpattern.composite.main;

import java.io.FileNotFoundException;

/**
 * Composite 패턴에서의 메인 추상 클래스
 * - 컨테에너와 아이템을 동일시 하기 위한 클래스
 * - 파일(File) 및 폴더(Directory) 클래스를 동일시 하여 재귀적인 구조를 만들기 위한 클래스
 */
public abstract class Entry {
    protected Entry parent;

    public abstract String getName();

    public abstract int getSize();

    public Entry add(Entry entry) throws FileNotFoundException {
        // 파일인 경우 해당 예외가 발생
        throw new FileTreatmentException();
    }

    // 템플릿 메서드 역할
    public void printList() {
        printList("");
    }

    protected abstract void printList(String prefix);

    @Override
    public String toString() {
        return String.format("%s (%d)", getName(), getSize());
    }

    // Exercise 2
    public String getFullPath() {
        StringBuilder builder = new StringBuilder();
        if (parent != null) {
            builder.append(parent.getFullPath());
        }
        builder.append("/").append(getName());
        return builder.toString();
    }
}
