package designpattern.ChainOfResponsibility.main.handler;

import designpattern.ChainOfResponsibility.main.trouble.Trouble;

public class SpecialSupport extends Support {
    private final int target;

    public SpecialSupport(String name, int target) {
        super(name);
        this.target = target;
    }

    @Override
    protected boolean resolve(Trouble trouble) {
        // 지정한 번호에 대해서만 처리
       return trouble.getId() == target;
    }
}
