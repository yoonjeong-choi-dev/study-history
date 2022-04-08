package designpattern.proxy.main.subject;

/**
 * Proxy 역할과 RealSubject 역할을 동일시 하기 위한 인터페이스
 * - 두 개의 역할을 동일시 하는 API 제공
 * - 클라이언트 측에서는 해당 객체가 프록시인지 실제 객체인지 모르는 상태로 API 사용 가능
 */
public interface Printable {
    void setPrinterName(String name);

    String getPrinterName();

    void print(String string);
}
