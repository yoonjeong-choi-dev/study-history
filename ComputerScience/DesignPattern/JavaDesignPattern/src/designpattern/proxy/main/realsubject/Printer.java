package designpattern.proxy.main.realsubject;

import designpattern.proxy.main.subject.Printable;

/**
 * RealSubject 역할
 * - 실제 사용자의 요구 사항을 처리해야 하는 클래스
 * - 인스턴스 생성에 오랜 시간이 걸리는 클래스로, Proxy 클래스에 의해 늦은 생성을 하게 됨
 * - 단, 해당 클래스 자체는 프록시의 존재 자체를 모름
 */
public class Printer implements Printable {

    private String name;

    public Printer() {
        heavyJob("Printer Instance is creating");
    }

    public Printer(String name) {
        this.name = name;
        heavyJob(String.format("Printer Instance(%s) is creating", name));
    }

    // 인스턴스 생성이 오래걸리는 것을 시뮬레이션하기 위한 메서드
    private void heavyJob(String message) {
        System.out.print(message);
        for (int i = 0; i < 5; i++) {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.print(".");
        }
        System.out.println("COMPLETE!");
    }

    @Override
    public void setPrinterName(String name) {
        this.name = name;
    }

    @Override
    public String getPrinterName() {
        return name;
    }

    @Override
    public void print(String string) {
        System.out.printf("=== %s ===\n", name);
        System.out.println(string);
    }
}
