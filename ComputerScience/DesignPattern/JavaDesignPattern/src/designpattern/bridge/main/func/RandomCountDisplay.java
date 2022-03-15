package designpattern.bridge.main.func;

import designpattern.bridge.main.impl.DisplayImpl;

import java.util.Random;

// Exercise 1
public class RandomCountDisplay extends CountDisplay {
    Random random = new Random();

    public RandomCountDisplay(DisplayImpl impl) {
        super(impl);
    }

    public void randomDisplay(int times) {
        multiDisplay(random.nextInt(times));
    }
}
