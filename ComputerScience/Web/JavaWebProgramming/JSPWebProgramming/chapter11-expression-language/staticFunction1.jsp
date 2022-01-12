<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>

<%-- 정의한 태그 라이브러리(tld) 임포트 : myFunc 를 사용하여 호출 가능 --%>
<%@ taglib prefix="myFunc" uri="/WEB-INF/tlds/el-functions.tld" %>

<%
    request.setAttribute("price", 7166);
%>
<html>
<head>
    <title>정적 메서드 호출 1</title>
<head>
<body>
<%-- tld 파일에서 설정한 <function> 태그의 <name> 으로 호출--%>
가격은 <b>${myFunc:yjNumberFormat(price, '#,##0')}</b>원 입니다.
</body>
</html>