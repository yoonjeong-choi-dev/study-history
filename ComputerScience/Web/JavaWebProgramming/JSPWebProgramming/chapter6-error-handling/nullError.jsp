<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%-- page 디렉티브 : 에러 페이지 경로 설정 --%>
<%@ page errorPage="/errors/viewErrorMessage.jsp" %>
<html>
<head>
    <title>에러 발생페이지</title>
<head>
<body>
    name 파라미터 값 : <%= request.getParameter("name").toUpperCase() %>
</body>
</html>