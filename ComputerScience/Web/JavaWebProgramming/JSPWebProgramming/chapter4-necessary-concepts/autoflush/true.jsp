<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%-- 출력 버퍼 플러시 설정 : 플러시하고 계속 작업 진행  --%>
<%@ page buffer="1kb" autoFlush="true" %>
<html>
<head>
    <title>autoflush - true</title>
<head>
<body>

<% for(int i=0;i<100;i++) {%>
    1234
<% }%>

</body>
</html>