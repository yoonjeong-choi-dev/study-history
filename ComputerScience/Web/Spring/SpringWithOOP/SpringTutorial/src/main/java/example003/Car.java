package example003;

public class Car {
	Tire tire;

	public Tire getTire() {
		return tire;
	}
	
	public void setTireTest(Tire tire) {
		this.tire = tire;
	}
	
	public String getTireBand() {
		return "������ Ÿ�̾� : " + tire.getBrand();
	}
}
