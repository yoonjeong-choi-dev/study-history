package example.anonymousBean;

import org.springframework.context.support.ClassPathXmlApplicationContext;

public class Test {
    public static void main(String[] args) {
        ClassPathXmlApplicationContext ctx = new ClassPathXmlApplicationContext("example/anonymousBean/beans.xml");

        System.out.println("[컨테이너에 보관된 객체 이름 출력]");
        for (String name : ctx.getBeanDefinitionNames()) {
            System.out.println(name);
        }

        System.out.println("[익명 빈 꺼내기]");
        Score score1 = (Score) ctx.getBean("example.anonymousBean.Score");
        Score score2 = (Score) ctx.getBean("example.anonymousBean.Score#0");
        Score score3 = (Score) ctx.getBean("example.anonymousBean.Score#1");

        if(score1 == score2) System.out.println("Score == Score#0");
        if(score1 != score3) System.out.println("Score != Score#1");

        //System.out.println("[클래스 타입으로 빈 꺼내기]");
        //Score score4 = (Score) ctx.getBean(example.anonymousBean.Score.class);

    }
}
