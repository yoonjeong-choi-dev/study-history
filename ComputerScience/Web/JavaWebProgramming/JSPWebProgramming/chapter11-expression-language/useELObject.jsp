<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%
    // 테스트용 설정들
    request.setAttribute("name", "최윤정");

    Cookie cookie = new Cookie("name", "Yoonjeong");
    response.addCookie(cookie);
%>
<html>
<head>
    <title>EL 기본객체</title>
<head>
<body>
요청 URI : ${pageContext.request.requestURI} <br>
request name 속성 : ${requestScope.name} <br>
code params : ${param.code} <br>
cookie.name : ${cookie.name.value}<br>
</body>
</html>