<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>

<%
	String id = request.getParameter("id");
	if (id != null && id.equals("yjchoi")) {
        // jsp-programming/chapter3-jsp-intro/redirect.jsp?id=yjchoi 로 접근 시 리다이렉트
		response.sendRedirect("/jsp-programming/chapter3-jsp-intro/");
	} else {
%>
<html>
<head>
    <title>로그인에 실패</title>
</head>
<body>
잘못된 아이디입니다.
</body>
</html>
<%
	}
%>
