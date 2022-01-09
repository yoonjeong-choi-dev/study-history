<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%-- page 디렉티브 : 패키지 import --%>
<%@ page import="java.util.Calendar" %>
<html>
<head>
    <title>Calendar 모듈 임포트</title>
<head>
<body>
<%-- 스크립트 요소 --%>
<%
    Calendar cal = Calendar.getInstance();
%>
오늘은
    <%= cal.get(Calendar.YEAR)%>년
    <%= cal.get(Calendar.MONTH) + 1%>월
    <%= cal.get(Calendar.DATE) %>일
입니다.
</body>
</html>