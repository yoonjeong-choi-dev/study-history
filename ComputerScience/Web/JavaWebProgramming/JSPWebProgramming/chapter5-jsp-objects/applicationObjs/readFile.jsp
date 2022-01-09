<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>

<%@ page import="java.io.*" %>
<%@ page import="java.net.URL" %>
<html>
<head>
    <title>리소스 접근</title>
<head>
<body>
<%
    String path = "/chapter5-jsp-objects/applicationObjs/static-text.txt";
    char[] buff = new char[128];
    int len;
%>

<h1>getRealPath 메서드</h1>
자원의 시스템 경로 : <br>
<%= application.getRealPath(path) %> <br>
--------<br>
<strong> getResourceAsStream 메서드를 이용한 스트림 생성 </strong> <br>
--------<br>
<%
    len = -1;
    try (InputStreamReader br = new InputStreamReader(
        application.getResourceAsStream(path), "utf-8")) {
        while((len = br.read(buff)) != -1) {
            out.print(new String(buff, 0, len));
        }
    }
    catch(IOException ex) {
        out.println("IO Exception : " + ex.getMessage());
    }
%>

--------<br>
<strong> getResource 메서드를 이용한 URL 접근 </strong> <br>
<%
    URL url = application.getResource(path);
%>
자원의 url : <br>
<%= url.toString() %> <br>
--------<br>
<%
    len = -1;
    try (InputStreamReader br = new InputStreamReader(
        url.openStream(), "utf-8")) {
        while((len = br.read(buff)) != -1) {
            out.print(new String(buff, 0, len));
        }
    }
    catch(IOException ex) {
        out.println("IO Exception : " + ex.getMessage());
    }
%>
    
</body>
</html>