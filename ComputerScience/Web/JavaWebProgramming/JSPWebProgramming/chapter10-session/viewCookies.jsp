<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>

<%@ page import="java.net.URLDecoder" %>
<html>
<head>
    <title>쿠키 읽기</title>
<head>
<body>
쿠키 목록 <br>
<%
    Cookie[] cookies = request.getCookies();
    if (cookies != null && cookies.length > 0) {
        for(int i=0;i<cookies.length;i++) {    
%>
    <%= cookies[i].getName() %> : <%=URLDecoder.decode(cookies[i].getValue(), "utf-8") %> [<%= cookies[i].getDomain()%>]<br>
<%
        }
    } else {
%>
    쿠키가 존재하지 않습니다...
<%
    }
%>
</body>
</html>