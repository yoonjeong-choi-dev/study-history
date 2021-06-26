package example001_03;

import static org.junit.Assert.assertEquals;

import org.junit.Test;



public class CarTest {
	@Test
	public void KoreaTireCarTest() {
		Tire tire1 = new KoreaTire();
		Car car = new Car();
		car.setTire(tire1);
		assertEquals("장착된 타이어 : Korea Tire", car.getTireBand());
	}
	
	@Test
	public void AmericaTireCarTest() {
		Tire tire2 = new AmericaTire();
		Car car = new Car();
		car.setTire(tire2);
		assertEquals("장착된 타이어 : Ameraica Tire", car.getTireBand());
	}
}
