package di.factoryMethod;

import org.springframework.context.support.ClassPathXmlApplicationContext;

public class Test {
    public static void main(String[] args) {
        ClassPathXmlApplicationContext ctx = new ClassPathXmlApplicationContext("di/factoryMethod/beans.xml");


        System.out.println("[Static Factory Method]");
        Tire tire1 = (Tire) ctx.getBean("tire1");
        System.out.println(tire1);

        Tire tire2 = (Tire) ctx.getBean("tire2");
        System.out.println(tire2);

        System.out.println("[Instance Factory Method]");
        Engine e1 = (Engine) ctx.getBean("e1");
        System.out.println(e1);

        Engine e2 = (Engine) ctx.getBean("e2");
        System.out.println(e2);

        System.out.println("[Spring Factory Bean]");
        Tire b1 = (Tire) ctx.getBean("beanT1");
        System.out.println(b1);

        Tire b2 = (Tire) ctx.getBean("beanT2");
        System.out.println(b2);
    }
}
