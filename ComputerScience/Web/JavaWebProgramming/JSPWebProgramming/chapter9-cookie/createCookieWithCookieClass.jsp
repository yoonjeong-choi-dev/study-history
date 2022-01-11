<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%-- 커스텀 클래스 임포트 --%>
<%@ page import="util.Cookies" %>
<%
    response.addCookie(Cookies.createCookie("customName", "Yoonjeong"));
    response.addCookie(Cookies.createCookie("customTest", "TestCookie"));
%>
<html>
<head>
    <title>쿠키 생성</title>
<head>
<body>
<a href="<%= request.getContextPath() %>/readCookie.jsp" >쿠키 확인 페이지</a> <br>
<a href="<%= request.getContextPath() %>/deleteCookie.jsp" >쿠키 삭제 페이지</a>
</body>
</html>