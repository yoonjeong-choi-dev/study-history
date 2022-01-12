<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>

<%-- 정적 메서드가 정의된 클래스 임포트 --%>
<%@ page import="util.FormatUtil" %>

<%
    request.setAttribute("price", 7166);
%>
<html>
<head>
    <title>정적 메서드 호출 2</title>
<head>
<body>
<%-- EL 3.0 버전부터는 직접 호출 가능--%>
가격은 <b>${FormatUtil.number(price, '#,##0')}</b>원 입니다.
</body>
</html>