<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%-- core 태그 임포트 --%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<html>
<head>
    <title>예외 처리</title>
<head>
<body>

<h4>0으로 나누기</h4>
<c:catch var="ex">
<% int divied = 10/0; %>
</c:catch>

<c:if test="${ex!=null}">
    예외 발생 : <br>
    ${ex}
</c:if>

</html>