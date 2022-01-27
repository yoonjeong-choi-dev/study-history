package example.beanName;

import org.springframework.context.support.ClassPathXmlApplicationContext;

public class Test {
    public static void main(String[] args) {
        ClassPathXmlApplicationContext ctx = new ClassPathXmlApplicationContext("example/beanName/beans.xml");

        System.out.println("[컨테이너에 보관된 객체 이름 출력]");
        for (String name : ctx.getBeanDefinitionNames()) {
            System.out.println(name);
        }

        System.out.println("[score2 별명 출력]");
        for(String alias : ctx.getAliases("score2")) {
            System.out.println(alias);
        }

        // 별명으로 빈 가져오기
        Score score = (Score) ctx.getBean("score");
        Score score2 = (Score) ctx.getBean("score2");
        Score score3 = (Score) ctx.getBean("score3");
        Score score4 = (Score) ctx.getBean("score4");
        Score scoreOk = (Score) ctx.getBean("score-ok!");

        System.out.println("[가져온 빈 확인]");
        if (score != null) System.out.println("score");
        if (score2 != null) System.out.println("score2");
        if (score3 != null) System.out.println("score3");
        if (score3 != null) System.out.println("score4");
        if (scoreOk != null) System.out.println("score-ok!");

        System.out.println("[생성된 빈 비교]");
        if (score == score2) System.out.println("score == score2");
        if (score2 == score3) System.out.println("score2 == score3");
        if (score3 == score4) System.out.println("score3 == score4");
        if (score4 == scoreOk) System.out.println("score4 == scoreOk");
    }
}
