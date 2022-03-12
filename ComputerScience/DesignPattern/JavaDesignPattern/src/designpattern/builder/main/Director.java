package designpattern.builder.main;

/**
 * Builder 추상 클래스에서 정의한 API를 사용하여 인스턴스를 생성
 * - 클라이언트에서 사용하는 객체
 * - 생성자를 통해 Builder 구체 클래스의 인스턴스를 주입
 * - 주입받은 인스턴스를 추상 클래스에서 제공하는 API를 이용하여 단계를 밟으면서 전체적인 구조를 구축
 * -- Builder 클래스에서 제공하는 복잡한 API를 하나의 메서드(construct)로 단순화하여 클라이언트에 제공
 */
public class Director {
    private final Builder builder;
    public Director(Builder builder) {
        this.builder = builder;
    }

    public void construct() {
        builder.makeTitle("Greeting");

        builder.makeString("Morning and Afternoon");
        builder.makeItems(new String[] {
                "Good Morning~",
                "Hello~~"
        });

        builder.makeString("Night");
        builder.makeItems(new String[] {
                "Hello~",
                "Good Night!",
                "Bye Bye~~"
        });
        builder.close();
    }
}
