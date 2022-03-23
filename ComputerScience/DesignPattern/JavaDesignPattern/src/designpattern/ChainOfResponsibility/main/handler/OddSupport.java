package designpattern.ChainOfResponsibility.main.handler;

import designpattern.ChainOfResponsibility.main.trouble.Trouble;

public class OddSupport extends Support {

    public OddSupport(String name) {
        super(name);
    }

    @Override
    protected boolean resolve(Trouble trouble) {
        // 트러블의 id가 홀수인 경우에만 해결
        return trouble.getId() % 2 == 1;
    }
}
