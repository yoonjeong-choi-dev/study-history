package multiserver;

import java.io.PrintStream;
import java.net.Socket;
import java.util.Scanner;

// 요청 처리를 위한 워커 스레드
// server.CalculatorServer의 processRequest에 해당하는 작업 수행
public class CalculatorWorker extends Thread {
    static int count;

    Socket socket;
	Scanner in;
	PrintStream out;
	int workerId;

    public CalculatorWorker(Socket socket) throws Exception {
		workerId = ++count;
		this.socket = socket;
		in = new Scanner(socket.getInputStream());
		out = new PrintStream(socket.getOutputStream());
	}

    @Override
    public void run() {
        System.out.println("[thread-"+workerId+"] is running");

        String operator = null;
        double a, b, result;

        while(true) {
            try {
                operator = in.nextLine();

                if (operator.equals("goodbye")) {
                    out.println("Good Bye~");
                    break;
                } 
                a = Double.parseDouble(in.nextLine());
                b = Double.parseDouble(in.nextLine());

                switch (operator) {
					case "+": result = a + b; break;
					case "-": result = a - b; break;
					case "*": result = a * b; break;
					case "/": 
						if (b == 0) throw new Exception("0 으로 나눌 수 없습니다!");
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
        try {out.close();} catch (Exception e) {}
		try {in.close();} catch (Exception e) {}
		try {socket.close();} catch (Exception e) {}
        System.out.println("[thread-"+workerId+"] is closed");
    }
}
