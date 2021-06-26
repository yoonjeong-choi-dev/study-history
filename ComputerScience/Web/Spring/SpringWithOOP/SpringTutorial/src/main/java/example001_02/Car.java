package example001_02;

public class Car {
	Tire tire;

	public Car(Tire tire) {
		this.tire = tire;
	}

	public String getTireBand() {
		return "장착된 타이어 : " + tire.getBrand();
	}
}
