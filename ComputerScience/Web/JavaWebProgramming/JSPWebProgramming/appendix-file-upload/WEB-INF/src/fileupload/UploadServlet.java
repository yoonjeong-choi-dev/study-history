package fileupload;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Collection;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

public class UploadServlet extends HttpServlet {
    static final String FILEPATH = "/home/yjchoi/workspace/tomcat-webapps/";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
        throws IOException, ServletException{
        request.setCharacterEncoding("utf-8");
        response.setContentType("text/html; charset=utf-8");

        PrintWriter writer = response.getWriter();
        writer.println("<html><title>File Upload</title></html><body>");
        
        // form 데이터 형식 확인
        String contentType = request.getContentType();
        if (contentType != null && contentType.toLowerCase().startsWith("multipart/")) {
            printPartInfo(request, writer);
        } else {
            writer.println("<h1>멀티 파트폼이 아님</h1>");
        }
        writer.println("</body></html>");
    }

    private void printPartInfo(HttpServletRequest request, PrintWriter writer) 
        throws IOException, ServletException {
        writer.println("<h1>Multipart data</h1>");

        Collection<Part> parts = request.getParts();
        for (Part part : parts) {
            writer.println("<br> name = " + part.getName());

            String contentType = part.getContentType();
            writer.println("<br> contentType = " + contentType);

            if(part.getHeader("Content-Disposition").contains(("filename="))) {
                // 파일 타입인 경우 FILEPATH 저장
                writer.println("<br> file size = " + part.getSize());

                String fileName = part.getSubmittedFileName();
                writer.println("<br> filename = " + fileName);
                if(part.getSize() > 0) {
                    part.write(FILEPATH + fileName);
                    writer.println("<br><b>file is saved to " + FILEPATH +fileName);
                    part.delete();  // part와 관련된 임시 파일들 삭제
                }
            } else {
                String value = request.getParameter(part.getName());
                writer.println("<br>value = " + value);
            }

            writer.println("<hr/>");
        }
    }
}
