<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%-- 출력 버퍼 플러시 설정 : 버퍼가 다차면 에러 발생  --%>
<%@ page buffer="1kb" autoFlush="false" %>
<html>
<head>
    <title>autoflush - false</title>
<head>
<body>

<% for(int i=0;i<100;i++) {%>
    1234
<% }%>

</body>
</html>