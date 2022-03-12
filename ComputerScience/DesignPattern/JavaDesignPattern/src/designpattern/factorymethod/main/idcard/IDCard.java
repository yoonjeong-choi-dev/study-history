package designpattern.factorymethod.main.idcard;

import designpattern.factorymethod.main.framework.Product;

// 팩토리 패턴에서 실제 생성할 객체에 대한 정의
public class IDCard extends Product {
    private final String owner;
    private final int authNumber;

    // default 접근 제어자 사용
    // => 동일 패키지의 IDCard 객체를 생성하는 팩터리 구현체를 이용해서만 객체 생성을 가능하게 만든다
    IDCard(String owner, int authNumber) {
        System.out.printf("%s's card is created with auth number %d\n", owner, authNumber);
        this.owner = owner;
        this.authNumber = authNumber;
    }

    public String getOwner() {
        return owner;
    }

    public int getAuthNumber() {
        return authNumber;
    }

    @Override
    public void use() {
        System.out.printf("%s's card is used with auth number %d\n", owner, authNumber);
    }
}
