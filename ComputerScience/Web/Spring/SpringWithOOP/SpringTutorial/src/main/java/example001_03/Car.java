package example001_03;

public class Car {
	Tire tire;

	public Tire getTire() {
		return tire;
	}
	
	public void setTire(Tire tire) {
		this.tire = tire;
	}
	
	public String getTireBand() {
		return "������ Ÿ�̾� : " + tire.getBrand();
	}
}
