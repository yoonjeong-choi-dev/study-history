package mvc.controller;

import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Properties;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import mvc.command.CommandHandler;
import mvc.command.NullHandler;

// 설정 파일을 읽어와 (명령어, 핸들러) 매핑 정보를 받아옴
// => 새로운 명령어가 추가되어도 빌드 필요없이 설정 파일만 변경하면 된다
public class ControllerUsingFile extends HttpServlet {
    // (명령어, 핸들러) 매핑 정보 저장
    private Map<String, CommandHandler> commandHandlerMap = new HashMap<>();

    // 0단계 : 매핑 정보를 프로퍼티 파일에서 읽어와서 저장
    @Override
    public void init() throws ServletException {
        String configFile = getInitParameter("configFile");
        Properties prop = new Properties();

        // 프로퍼티 파일 읽기
        String configFilePath = getServletContext().getRealPath(configFile);
        try (FileReader fis = new FileReader(configFilePath)) {
            prop.load(fis);
        } catch (IOException ex) {
            throw new ServletException(ex);
        }

        // 매핑 정보 저장
        Iterator keyItr = prop.keySet().iterator();
        while (keyItr.hasNext()) {
            String command = (String) keyItr.next();
            String handlerClassName = prop.getProperty(command);

            try {
                // 클래스 이름을 이용하여 핸들러 객체 생성 및 맵에 저장
                Class<?> handlerClass = Class.forName(handlerClassName);
                CommandHandler handlerInstance = (CommandHandler) handlerClass.newInstance();
                commandHandlerMap.put(command, handlerInstance);
            } catch (ClassNotFoundException | InstantiationException | IllegalAccessException ex) {
                throw new ServletException(ex);
            }
        }
    }

    // 1단계 : HTTP 요청 받기
    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
                request.setCharacterEncoding("utf-8");
                process(request, response);
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
                request.setCharacterEncoding("utf-8");
                process(request, response);
    }

    private void process(HttpServletRequest request, HttpServletResponse response)
            throws IOException, ServletException {

        // 요청 타입에 대응하는 커맨드 핸들러 호출
        String command = request.getParameter("cmd");
        CommandHandler handler = commandHandlerMap.get(command);
        if (handler == null) {
            handler = new NullHandler();
        }
        String viewPage = null;
        try {
            viewPage = handler.process(request, response);
        } catch (Exception ex) {
            throw new ServletException(ex);
        }

        if (viewPage != null ) {
            RequestDispatcher dispatcher = request.getRequestDispatcher(viewPage);
            dispatcher.forward(request, response);
        }

    }
}
