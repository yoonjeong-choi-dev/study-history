package designpattern.state.main;

import designpattern.state.main.context.SafeFrame;

public class Main {
    public static void main(String[] args) {
        SafeFrame frame = new SafeFrame("State Pattern");
        while (true) {
            for(int hour = 0;hour<24;hour++){
                frame.setClock(hour);
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
