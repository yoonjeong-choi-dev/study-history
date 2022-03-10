package designpattern.templatemethod.headfirst.abstractclass;

public abstract class CaffeineBeverageWithHook {
    // 템플릿 메서드
    public final void prepareRecipe() {
        init();
        boilWater();
        brew();
        pourInCup();

        if(customerWantsCondiments()) {
            addCondiments();
        }
    }

    abstract protected void init();

    protected void boilWater() {
        System.out.println("Boiling water");
    }

    abstract protected void brew();

    protected void pourInCup() {
        System.out.println("Pouring the beverage in the cup");
    }

    // hook : 추상 클래스에서 기본적으로 제공하나 구현 클래스에서 오버라이드가 가능한 메서드
    // => 알고리즘에서 선택적으로 필요한 단계가 있는 경우 사용
    protected boolean customerWantsCondiments() {
        return true;
    }

    abstract protected void addCondiments();
}
