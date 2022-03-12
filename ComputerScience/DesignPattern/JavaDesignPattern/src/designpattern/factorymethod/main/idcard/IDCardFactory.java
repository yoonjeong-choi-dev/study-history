package designpattern.factorymethod.main.idcard;

import designpattern.factorymethod.main.framework.Factory;
import designpattern.factorymethod.main.framework.Product;

import java.util.HashMap;

// 팩토리 패턴에서 실제 생성할 객체를 생성하는 팩토리 구현
public class IDCardFactory extends Factory {
    // private List<String> owners = new ArrayList<>();
    private final HashMap<String, Integer> owners = new HashMap<>();
    private int authNumber = 123;

    @Override
    protected Product createProduct(String user) {
        return new IDCard(user, authNumber++);
    }

    @Override
    protected void registerProduct(Product product) {
        IDCard idCard = (IDCard) product;
        owners.put(idCard.getOwner(), idCard.getAuthNumber());
    }

    public HashMap<String, Integer> getOwners() {
        return owners;
    }
}
