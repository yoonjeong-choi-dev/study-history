<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%
    String id = request.getParameter("id");
    String pw = request.getParameter("password");

    if (id==null || pw == null) {

%>
        <jsp:forward page="./loginForm.jsp">
            <jsp:param name="error" value="Redirect due to invalid path"/>
        </jsp:forward>
<%
    }
%>
<%
    // 패스워드 체크
    if (id.equals(pw)) {
        // 세션 생성
        session.setAttribute("AUTH", id);
%>
<html>
<head>
    <title>로그인 결과</title>
<head>
<body>
<h1>Success to Sign In! </h1>
세션 로그인 정보가 저장되어있는지 확인하세요!
<a href="<%= request.getContextPath()%>/auth/loginCheck.jsp">로그인 체크</a>
<br>
<a href="<%= request.getContextPath()%>/auth/loginForm.jsp">로그인 폼으로 이동</a>
<%
    } else { // 로그인 실패    
%>
<script>
alert("Fail to Sign In..");
history.go(-1);
</script>
<% } %>
</body>
</html>