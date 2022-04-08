package designpattern.proxy.main.proxy;

import designpattern.proxy.main.realsubject.Printer;
import designpattern.proxy.main.subject.Printable;

/**
 * Proxy 역할을 하는 클래스
 * - 클라이언트의 요구를 할 수 있는 만큼 처리
 * - 자신이 처리하지 못하는 요구는 RealSubject 객체 생성 후 위임
 * - RealSubject 객체 null 체크는 멀티스레드 환경을 위해서 synchronized 키워드 추가(싱글톤의 늦은 초기화와 같은 이유)
 */
public class PrinterProxy implements Printable {
    private String name;
    private Printable real;   // 자신이 대리하는 본체
    private String subjectClassName;    // 본체 클래스 이름

    public PrinterProxy() {

    }

    public PrinterProxy(String name) {
        this.name = name;
    }

    public PrinterProxy(String name, String subjectClassName) {
        this.name = name;
        this.subjectClassName = subjectClassName;
    }

    @Override
    public synchronized void setPrinterName(String name) {
        if (real != null) {
            real.setPrinterName(name);
        }

        this.name = name;
    }

    @Override
    public String getPrinterName() {
        return name;
    }

    @Override
    public void print(String string) {
        // 이 요구 사항은 프록시에서 처리 하지 못함 => 본인에게 위임
        realize();
        real.print(string);
    }

    private synchronized void realize() {
        if (real == null) {

            if (subjectClassName == null) {
                real = new Printer(name);
            } else {
                // 클래스 이름이 있는 경우 해당 클래스 이름으로 로드
                try {
                    real = (Printable) Class.forName(subjectClassName).newInstance();
                    real.setPrinterName(name);
                } catch (ClassNotFoundException | InstantiationException | IllegalAccessException e) {
                    System.err.printf("Cannot found %s => Create default subject\n", subjectClassName);
                    real = new Printer(name);
                }
            }

        }
    }
}
