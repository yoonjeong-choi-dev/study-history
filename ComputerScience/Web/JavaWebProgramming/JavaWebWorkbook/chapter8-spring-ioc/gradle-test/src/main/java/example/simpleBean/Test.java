package example.simpleBean;

import org.springframework.context.support.ClassPathXmlApplicationContext;

public class Test {
    public static void main(String[] args) {
        ClassPathXmlApplicationContext ctx = new ClassPathXmlApplicationContext("example/simpleBean/beans.xml");

        Score score = (Score) ctx.getBean("score");

        System.out.println("Sum : " + score.sum());
        System.out.println("Avg : " + score.average());
    }
}
