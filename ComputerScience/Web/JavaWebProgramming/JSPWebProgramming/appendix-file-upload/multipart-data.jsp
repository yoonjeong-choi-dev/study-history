<%@ page contentType="text/html; charset=UTF-8" %>
<%@ page trimDirectiveWhitespaces="true" %>

<%@ page import="java.io.InputStream" %>
<%@ page import="java.io.IOException" %>

<html>
<head>
    <title>파일 업로드 데이터</title>
<head>
<body>
<%
    InputStream is = null;
    
    out.println("<h1>getContentType</h1>");
    out.print("[");
    out.print(request.getContentType());
    out.println("]");
    out.println("<br><br>");
    try {
        out.println("<h1>Stream data</h1>");
        is = request.getInputStream();
        int data = -1;
        
        while ( (data = is.read()) != -1 ) {
            out.print((char)data);
        }
    } finally {
        if (is != null) try { is.close(); } catch(IOException ex) {}
    }
%>


</form>
</body>
</html>