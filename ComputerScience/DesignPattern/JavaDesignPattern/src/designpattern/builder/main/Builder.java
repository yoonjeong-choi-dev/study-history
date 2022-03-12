package designpattern.builder.main;

/**
 * 빌더 패턴의 메인 추상 클래스
 * - Builder 하위 클래스의 객체를 빌드(build)하기 위한 메서드들을 선언
 * - 구체 클래스의 객체를 구축하기 위한 API 결정
 * - Director 클래스를 이용하여 구체 클래스의 객체를 생성
 */
public abstract class Builder {
    // Exercise 2. 템플릿 메서드 패턴을 이용하여 호출 순서 제약
    private boolean initTitle = false;

    public void makeTitle(String title) {
        if (!initTitle) {
            buildTitle(title);
            initTitle = true;
        }
    }

    public void makeString(String string) {
        if (initTitle) buildString(string);
    }

    public void makeItems(String[] items) {
        if (initTitle) buildItems(items);
    }

    public void close() {
        if (initTitle) buildClose();
    }

    public abstract void buildTitle(String title);

    public abstract void buildString(String string);

    public abstract void buildItems(String[] items);

    public abstract void buildClose();

//    public abstract void makeTitle(String title);
//    public abstract void makeString(String string);
//    public abstract void makeItems(String[] items);
//    public abstract void close();
}
