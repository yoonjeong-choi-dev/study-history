package example.beanProperty;

import org.springframework.context.support.ClassPathXmlApplicationContext;

public class Test {
    public static void main(String[] args) {
        ClassPathXmlApplicationContext ctx = new ClassPathXmlApplicationContext("example/beanProperty/beans.xml");

        Score score1 = (Score) ctx.getBean("score1");
        System.out.println(score1);

        Score score2 = (Score) ctx.getBean("score2");
        System.out.println(score2);
    }
}
