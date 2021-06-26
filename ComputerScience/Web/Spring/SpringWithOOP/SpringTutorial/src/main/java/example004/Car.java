package example004;

import org.springframework.beans.factory.annotation.Autowired;

public class Car {
	@Autowired
	Tire tire;
	
	public String getTireBand() {
		return "장착된 타이어 : " + tire.getBrand();
	}
}
