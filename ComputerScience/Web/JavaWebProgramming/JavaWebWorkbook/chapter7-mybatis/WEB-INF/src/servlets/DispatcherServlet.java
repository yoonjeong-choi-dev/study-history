package servlets;

import java.io.IOException;
import java.util.HashMap;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import bind.DataBinding;
import bind.ServletRequestDataBinder;
import controls.Controller;
import listeners.ContextLoader;
import context.ApplicationContext;

@WebServlet("*.do")
public class DispatcherServlet extends HttpServlet {

    @Override
    protected void service(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // 페이지 인클루딩을 하는 경우, 응답의 컨텐츠 타입을 정의해줘야 함
        response.setContentType("text/html; charset=utf-8");

        String servletPath = request.getServletPath();
        try {
            // 애플리케이션 컨텍스트 가져오기
            ApplicationContext ctx = ContextLoader.getApplicationContext();

            // 컨트롤러로 전달할 모델 생성 및 필요한 정보 저장
            HashMap<String, Object> model = new HashMap<String, Object>();
            model.put("session", request.getSession());

            // 컨텍스트 로더에서 설정한 컨트롤러들에서 현재 요청을 수행할 컨트롤러 저장
            Controller pageController = (Controller) ctx.getBean(servletPath);

            if (pageController == null){
                request.setAttribute("error", "요청한 서비스는 찾을 수 없습니다");

                RequestDispatcher rd = request.getRequestDispatcher("/view/ClientError.jsp");
                rd.forward(request, response);
            }

            // 페이지 컨트롤러가 필요한 데이터가 있는 경우, 데이터 준비
            if (pageController instanceof DataBinding) {
                prepareRequestData(request, model, (DataBinding) pageController);
            }

            // 요청에 맞는 서비스 실행 및 URL 뷰
            String viewUrl = pageController.execute(model);

            // 서비스 결과 request에 저장
            for (String key : model.keySet()) {
                request.setAttribute(key, model.get(key));
            }

            if (viewUrl.startsWith("redirect:")) {
                response.sendRedirect(viewUrl.substring(9));
                return;
            } else {
                RequestDispatcher rd = request.getRequestDispatcher(viewUrl);
                rd.include(request, response);
            }
        } catch (Exception ex) {
            ex.printStackTrace();
            request.setAttribute("error", ex);

            RequestDispatcher rd = request.getRequestDispatcher("/view/ServerError.jsp");
            rd.forward(request, response);
        }
    }

    private void prepareRequestData(HttpServletRequest request,
            HashMap<String, Object> model, DataBinding dataBinding)
            throws Exception {
        Object[] dataBinders = dataBinding.getDataBinders();

        String dataName = null;
        Class<?> dataType = null;
        Object dataObj = null;

        for (int i=0;i<dataBinders.length;i+=2) {
            dataName = (String) dataBinders[i];
            dataType = (Class<?>) dataBinders[i+1];
            dataObj = ServletRequestDataBinder.bind(request, dataType, dataName);

            model.put(dataName, dataObj);
        }
    }
}
