package designpattern.ChainOfResponsibility.main.handler;

import designpattern.ChainOfResponsibility.main.trouble.Trouble;

public class NoSupport extends Support {

    public NoSupport(String name) {
        super(name);
    }

    @Override
    protected boolean resolve(Trouble trouble) {
        // 아무것도 처리하지 않는 핸들
        return false;
    }
}
