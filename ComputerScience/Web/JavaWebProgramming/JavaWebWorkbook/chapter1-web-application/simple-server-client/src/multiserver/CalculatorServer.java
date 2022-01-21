package multiserver;

import java.net.ServerSocket;
import java.net.Socket;

public class CalculatorServer {
    private int port;

    public CalculatorServer(int port) {
        this.port = port;
    }

    public void service() throws Exception {
        ServerSocket serverSocket = new ServerSocket(port);
        System.out.println("Calculator Server startup");

        Socket socket = null;
        while (true) {
            try {

                // 클라이언트 요청 대기
                socket = serverSocket.accept();
                System.out.println("connected to clinet");

                // 요청이 오면 워커 스레드 생성 및 요청 처리
                new CalculatorWorker(socket).start();
            } catch (Throwable ex) {
                System.out.println("connection error!");
            }
        }
    }

    public static void main(String[] args) throws Exception {
        CalculatorServer app = new CalculatorServer(7166);
        app.service();
    }
}
