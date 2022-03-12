package designpattern.prototype.main.framework;

import java.util.HashMap;

/**
 * 프로토타입 패턴에서 실제 인스턴스를 복사하여 반환하는 역할을 하는 클래
 */
public class Manager {
    private final HashMap<String, Product> protoMap = new HashMap<>();

    // 복제할 프로토타입 인스턴스 등록
    public void register(String name, Product proto) {
        protoMap.put(name, proto);
    }

    // 프로토타입 인스턴스를 이용하여 객체 생성
    public Product create(String name) {
        Product p = protoMap.get(name);
        return p.createClone();
    }
}
