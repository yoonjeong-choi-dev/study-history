<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%-- 커스텀 클래스 임포트 --%>
<%@ page import="util.Cookies" %>
<%
    // 브라우저 요청에 포함된 쿠키 가져오기
    Cookies cookies = new Cookies(request);
%>
<html>
<head>
    <title>로그인 상태 확인</title>
<head>
<body>
<%
    if(cookies.exists("AUTH")) {
%>
    아이디 <%= cookies.getValue("AUTH")%>로 로그인한 상태
<% } else { %>
    로그인하지 않은 상태
<% } %>

</body>
</html>