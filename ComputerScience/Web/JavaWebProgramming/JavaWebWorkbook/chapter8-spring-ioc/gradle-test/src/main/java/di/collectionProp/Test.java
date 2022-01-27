package di.collectionProp;

import org.springframework.context.support.ClassPathXmlApplicationContext;

public class Test {
    public static void main(String[] args) {
        ClassPathXmlApplicationContext ctx = new ClassPathXmlApplicationContext("di/collectionProp/beans.xml");

        Tire tire = (Tire) ctx.getBean("spareTire");
        System.out.println(tire);

        Car myCar = (Car) ctx.getBean("myCar");
        System.out.println(myCar);
    }
}
