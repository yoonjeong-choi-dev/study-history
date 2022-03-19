package designpattern.visitor.main.element;

import java.io.FileNotFoundException;
import java.util.Iterator;

/**
 * Composite 패턴에서 사용한 디렉토리 시스템 재사용
 * Composite 패턴에서의 방문자 패턴 적용
 * - 방문을 위한 Element 인터페이스 구현
 * - 실제 구현은 하위 구체 클래스에서 담당
 */
public abstract class Entry implements Element {
    public abstract String getName();

    public abstract int getSize();

    public Entry add(Entry entry) throws FileNotFoundException {
        // 파일인 경우 해당 예외가 발생
        throw new FileTreatmentException();
    }

    public Iterator<Entry> iterator() throws FileNotFoundException {
        // 파일인 경우 해당 예외 발생
        throw new FileTreatmentException();
    }

    @Override
    public String toString() {
        return String.format("%s (%d)", getName(), getSize());
    }
}
