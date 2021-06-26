package example003;

import static org.junit.Assert.assertEquals;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration("example003.xml")
public class CarTest {
	@Autowired
	Car car;
	
	@Test
	public void AmericaTireTest() {
		assertEquals("장착된 타이어 : Ameraica Tire", car.getTireBand());
	}
}
