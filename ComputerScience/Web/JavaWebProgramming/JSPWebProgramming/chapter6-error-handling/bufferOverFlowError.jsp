<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%-- 버퍼 에러로 인한 응답 코드 예외 --%>
<%@ page buffer="1kb" %>
<%@ page errorPage="/errors/viewErrorMessage.jsp" %>
<html>
<head>
    <title>Buffer Error</title>
<head>
<body>
버퍼 오버플로우 예외 <br>
버퍼 플러시 이후 예외 발생 시, 상태 코드 200 <br>
관련 에러 페이지들이 문서의 바로 밑에 생김<br>
예외 발생 이전에 버퍼가 플러시 될 가능성이 있으면 버퍼 크기들 늘려야함! <br>

<%-- 버퍼 오버 플로우 관련 예외--%>
<%
    for(int i=0; i<300;i++) {
        out.println(i);
    } 
%>

<%-- 산술관련 예외 --%>
<%= 1/0 %>
</body>
</html>