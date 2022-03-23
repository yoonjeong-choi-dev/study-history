package designpattern.ChainOfResponsibility.main.handler;

import designpattern.ChainOfResponsibility.main.trouble.Trouble;

public class LimitSupport extends Support {

    private final int upperBound;

    public LimitSupport(String name, int upperBound) {
        super(name);
        this.upperBound = upperBound;
    }

    @Override
    protected boolean resolve(Trouble trouble) {
        // 트러블의 id가 upperBound보다 낮은 경우에만 해결
        if (trouble.getId() < upperBound) {
            return true;
        } else {
            return false;
        }
    }
}
