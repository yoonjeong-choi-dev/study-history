package designpattern.bridge.main.func;

import designpattern.bridge.main.impl.DisplayImpl;

public class IncreaseDisplay extends CountDisplay {
    public IncreaseDisplay(DisplayImpl impl) {
        super(impl);
    }

    public void increaseDisplay(int count) {
        for (int i = 0; i < count; i++) {
            multiDisplay(i);
        }
    }
}
