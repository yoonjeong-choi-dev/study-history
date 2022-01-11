<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%
    Cookie cookie = new Cookie("user", "");
    cookie.setMaxAge(0);    // 유효시간을 0으로 설정함으로써 삭제
    response.addCookie(cookie);
%>
<html>
<head>
    <title>쿠키 생성</title>
<head>
<body>
<a href="<%= request.getContextPath() %>/readCookie.jsp" >쿠키 확인 페이지</a>

</body>
</html>