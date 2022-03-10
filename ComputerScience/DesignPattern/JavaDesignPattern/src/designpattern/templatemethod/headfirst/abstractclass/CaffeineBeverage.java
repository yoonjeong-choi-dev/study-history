package designpattern.templatemethod.headfirst.abstractclass;

// 카페인 음료 제조를 위한 추상 클래스
public abstract class CaffeineBeverage {
    // 템플릿 메서드
    public final void prepareRecipe() {
        init();
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }

    abstract protected void init();

    protected void boilWater() {
        System.out.println("Boiling water");
    }

    abstract protected void brew();

    protected void pourInCup() {
        System.out.println("Pouring the beverage in the cup");
    }

    abstract protected void addCondiments();

}
