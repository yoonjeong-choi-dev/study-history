package server;

import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

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
                System.out.println("Waiting client...");

                // 하나의 클라이언트에 대해서 소켓 연결 허가
                socket = serverSocket.accept();
                System.out.println("connected to clinet");

                // 해당 소켓으로 연결이 끊길 때까지 작업 수행
                processRequest(socket);
                System.out.println("closed connection to client");
            } catch (Throwable ex) {
                System.out.println("connection error!");
            }
        }
    }

    private void processRequest(Socket socket) throws Exception {
        Scanner in = new Scanner(socket.getInputStream());
        PrintStream out = new PrintStream(socket.getOutputStream());

        String operator = null;
        double a, b, result;

        while (true) {
            try {
                operator = in.nextLine();

                if (operator.equals("goodbye")) {
                    out.println("Good Bye~");
                    break;
                }
                a = Double.parseDouble(in.nextLine());
                b = Double.parseDouble(in.nextLine());

                switch (operator) {
                    case "+":
                        result = a + b;
                        break;
                    case "-":
                        result = a - b;
                        break;
                    case "*":
                        result = a * b;
                        break;
                    case "/":
                        if (b == 0)
                            throw new Exception("0 으로 나눌 수 없습니다!");
                        result = a / b;
                        break;
                    default:
                        throw new Exception("해당 연산을 지원하지 않습니다!");
                }

                // 클라이언트로 성공 메시지 및 결과 출력
                out.println("success");
                out.println(result);
            } catch (Exception ex) {
                // 실패 메시지 및 이유 전송
                out.println("failuer");
                out.println(ex.getMessage());
            }
        }

        // 스트림 및 소켓 리소스 해제
        try {
            out.close();
        } catch (Exception e) {
        }
        try {
            in.close();
        } catch (Exception e) {
        }
        try {
            socket.close();
        } catch (Exception e) {
        }
    }

    public static void main(String[] args) throws Exception {
        CalculatorServer app = new CalculatorServer(7166);
        app.service();
    }
}