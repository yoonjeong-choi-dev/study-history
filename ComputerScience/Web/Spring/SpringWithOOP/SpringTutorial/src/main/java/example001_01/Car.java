package example001_01;

public class Car {
	Tire tire;

	public Car() {
		tire = new KoreaTire();
	}

	public String getTireBand() {
		return "������ Ÿ�̾� : " + tire.getBrand();
	}
}
