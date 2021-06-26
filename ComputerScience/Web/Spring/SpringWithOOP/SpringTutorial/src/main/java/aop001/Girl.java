package aop001;

public class Girl {
	public void runSomething() {
		System.out.println("Enter the house opening the door with the key");
		
		try {
			System.out.println("Cook meals");
		}
		catch(Exception ex) {
			if(ex.getMessage().equals("Fire in the house")) {
				System.out.println("Call 119");
			}
		}
		finally {
			System.out.println("Turn off the light and Sleep");
		}
		
		System.out.println("Lock the door and Go out");
	}
}
