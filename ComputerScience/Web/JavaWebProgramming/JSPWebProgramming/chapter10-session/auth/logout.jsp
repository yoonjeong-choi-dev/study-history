<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%
    // 로그인 관련 세션 삭제
    session.invalidate();
%>

<html>
<head>
    <title>로그아웃</title>
<head>
<body>
<h1>Success to Sign Out! </h1>

<a href="<%= request.getContextPath()%>/auth/loginCheck.jsp">로그인 체크</a> <br>
<a href="<%= request.getContextPath()%>/auth/loginForm.jsp">로그인 하기</a> <br>

</body>
</html>