<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>

<html>
<head>
    <title>Null Params</title>
<head>
<body>
<h1>Null Param 필터 적용</h1>
id 파라미터 : <%= request.getParameter("id") %> <br>
name 파라미터 : <%= request.getParameter("name") %> <br>
member 파라미터 : <%= request.getParameter("member") %> <br>
</body>
</html>