<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%
    // 현재 세션 야이디
    String id = session.getId();
    request.setAttribute("orignalId", id);
    // 세션의 삭제
    session.invalidate();
%>
<html>
<head>
    <title>세션 삭제</title>
<head>
<body>
<h1>세션 종료</h1>
<h3>종료 직전 세션 ID : <%= id %> <br>

<a href="<%= request.getContextPath()%>/viewSessionCookie.jsp">세션 속성 확인하기</a>
</body>
</html>