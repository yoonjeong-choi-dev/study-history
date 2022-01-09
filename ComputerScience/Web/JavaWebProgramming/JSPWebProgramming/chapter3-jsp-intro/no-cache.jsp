<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>

<%
	response.setHeader("Cache-Control", "no-cache");    // 브라우저가 자체적으로 캐시는 하여 뒤로가기 등을 할 떄 사용
    response.setHeader("Cache-Control", "no-store");    // 브라우저가 아예 캐시 저장 X
    response.setHeader("Pragma", "no-cache");
    response.setDateHeader("Expires", 1L);
%>

<html>
<head>
    <title>No Cache Page</title>
<head>
<body>
<h1> 헤더 설정을 통한 no cache 설정</h1>
    
</body>
</html>