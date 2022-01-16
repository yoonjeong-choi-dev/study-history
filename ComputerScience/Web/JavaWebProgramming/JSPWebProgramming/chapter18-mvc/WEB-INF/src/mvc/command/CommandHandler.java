package mvc.command;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

// 커맨드 패턴 : 요청 커맨드에 따라 로직을 수행하는 커맨드 인터페이스
public interface CommandHandler {
    // 특정 요청에 대한 로직 수행 후, 결과로 보여줄 jsp 페이지의 URI 리턴
    public String process(HttpServletRequest request, HttpServletResponse response)
        throws Exception;
}
