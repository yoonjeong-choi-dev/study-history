package designpattern.ChainOfResponsibility.main;

import designpattern.ChainOfResponsibility.main.trouble.Trouble;
import designpattern.ChainOfResponsibility.main.handler.*;

public class Main {
    public static void main(String[] args) {
        // 다양한 핸들러 인스턴스 생성
        Support noSup = new NoSupport("No");
        Support limitSup = new LimitSupport("Limit", 100);
        Support specialSup = new SpecialSupport("Special", 429);
        Support limitSup2 = new LimitSupport("Limit2", 200);
        Support oddSup = new OddSupport("Odd");
        Support limitSup3 = new LimitSupport("Limit3", 300);

        // 핸들러 체인 생성
        noSup.setNext(limitSup).setNext(specialSup).setNext(limitSup2).setNext(oddSup).setNext(limitSup3);

        // 다양한 트러블 생성
        for(int i=0;i<500;i+=33) {
            noSup.support(new Trouble(i));
        }
    }
}
