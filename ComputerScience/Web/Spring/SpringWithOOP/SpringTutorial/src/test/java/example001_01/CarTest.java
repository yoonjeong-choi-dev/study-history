package example001_01;

import static org.junit.Assert.*;
import org.junit.Test;

public class CarTest {
	@Test
	public void BrandTireTest() {
		Car car = new Car();
		assertEquals("������ Ÿ�̾� : Korea Tire", car.getTireBand());
	}
}
