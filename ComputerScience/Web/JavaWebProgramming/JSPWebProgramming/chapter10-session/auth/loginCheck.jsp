<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>

<%
    String memberId = (String) session.getAttribute("AUTH");
    boolean isLogin = memberId==null? false: true;
%>
<html>
<head>
    <title>로그인 상태 확인</title>
<head>
<body>
<%
    if(isLogin) {
%>
    아이디 <%= memberId %>로 로그인한 상태
<% } else { %>
    로그인하지 않은 상태
<% } %>

<br>
<a href="<%= request.getContextPath()%>/auth/loginForm.jsp">로그인 폼으로 이동</a>

</body>
</html>