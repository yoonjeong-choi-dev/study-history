<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>

<%@ page import="java.net.URLEncoder" %>
<%
    Cookie cookie = new Cookie("user", URLEncoder.encode("최윤정", "utf-8"));
    response.addCookie(cookie);
%>
<html>
<head>
    <title>쿠키 생성</title>
<head>
<body>
생성한 쿠키 값:<br>
<%= cookie.getName() %> : <%= cookie.getValue() %><br>
쿠키 유효시간 : <%= cookie.getMaxAge() %> <br>
쿠키 도메인 : <%= cookie.getDomain() %> <br>
<a href="<%= request.getContextPath() %>/readCookie.jsp" >쿠키 확인 페이지</a> <br>
<a href="<%= request.getContextPath() %>/deleteCookie.jsp" >쿠키 삭제 페이지</a>
</body>
</html>