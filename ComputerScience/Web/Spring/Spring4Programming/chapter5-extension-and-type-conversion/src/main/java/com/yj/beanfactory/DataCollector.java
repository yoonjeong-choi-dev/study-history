package com.yj.beanfactory;

public class DataCollector implements ThresholdRequired{
    private int threshold;

    @Override
    public void setThreshold(int threshold) {
        this.threshold = threshold;
    }

    public int getThreshold() {
        return threshold;
    }
}
