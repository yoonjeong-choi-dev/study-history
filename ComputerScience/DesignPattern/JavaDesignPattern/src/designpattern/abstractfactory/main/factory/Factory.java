package designpattern.abstractfactory.main.factory;

/**
 * 추상 공장 클래스
 * - 추상 제품(Page) 클래스의 인스턴스를 생성하는 API 결정
 * - 해당 클래스의 하위 구체 클래스의 이름을 인자로 받아 구체적인 공장을 반환하는 역할
 * - 구체적인 제품(Page) 및 부품(Tray, Link)을 생성하는 추상 메서드(API) 제공
 */
public abstract class Factory {
    public static Factory getFactory(String className) {
        Factory factory = null;
        try {
            // 인자로 받은 클래스 이름을 이용하여 클래스로더를 통해 동적으로 인스턴스 생성
            factory = (Factory) Class.forName(className).newInstance();
        } catch (ClassNotFoundException e) {
            System.err.printf("Class %s is not found\n", className);
        } catch (Exception e) {
            e.printStackTrace();
        }

        return factory;
    }

    public abstract Link createLink(String caption, String url);

    public abstract Tray createTray(String caption);

    public abstract Page createPage(String title, String author);
}
