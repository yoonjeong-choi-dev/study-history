<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%-- out 객체의 버퍼 정보 출력을 위한 설정--%>
<%@ page buffer="8kb" %>

<%
    // 조건에 따라 페이지를 출력할 때만 out 객체 사용
	String name = request.getParameter("name");
    out.println("<h1>");
	if (name != null) {
        
        out.println("Hello~ ");
        out.println(name);
    } else {
        out.println("I don't know your name...");
    }

    out.println("</h1>");
%>
<html>
<head>
    <title>out 기본 객체</title>
<head>
<body>
<h1>버퍼 정보 from out</h1>
buffer size : <%= out.getBufferSize() %> <br>
remaing size : <%= out.getRemaining() %> <br>
auto flush : <%= out.isAutoFlush() %> <br>
</body>
</html>