package designpattern.factorymethod.main.framework;

/**
 * 특정 객체(Product)를 생성하는 추상 클래스
 * 사용자 측은 new 키워드를 통해 특정 객체를 생성하지 않고, 팩토리 객체를 이용하여 객체 생성
 * - 생성해야 하는 객체의 클래스에 대한 의존성을 낮춤
 * 템플릿 메서드 패턴 적용
 * - 제품을 생성하는 create 메서드가 템플릿 메서드
 * - create 메서드 내부에서 추상 메서드들이 호출
 */
public abstract class Factory {
    // 템플릿 메서드
    public final Product create(String user) {
        Product product = createProduct(user);
        registerProduct(product);
        return product;
    }

    // 추상 클래스 => 하위 클래스에게 구체적인 생성 방식 위임
    protected abstract Product createProduct(String user);

    protected abstract void registerProduct(Product product);
}
