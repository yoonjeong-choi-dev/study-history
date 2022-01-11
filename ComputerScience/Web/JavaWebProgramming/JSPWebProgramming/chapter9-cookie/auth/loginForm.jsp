<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>

<% 
    String error = request.getParameter("error");
%>
<html>
<head>
    <title>로그인 폼</title>
<head>
<body>
<% 
    if (error != null) {
%>
    <h1> <%= error%> </h1>
<% } %>
테스트 계정 : 아이디와 암호가 동일해야함 <br>
<form action="<%= request.getContextPath()%>/auth/login.jsp" method="POST">
    아이디 : <input type="text" name="id" size="10" />
    암호 : <input type="password" name="password" size="20"/>
    <input type="submit" value="Sign In" />
</form>

이미 로그인을 하셨으면 아래 링크를 클릭하세요!
<a href="<%= request.getContextPath()%>/auth/loginCheck.jsp">로그인 체크</a> <br>

<a href="<%= request.getContextPath()%>/auth/logout.jsp" style="border: 1px solid;">로그아웃</a>
    
</body>
</html>