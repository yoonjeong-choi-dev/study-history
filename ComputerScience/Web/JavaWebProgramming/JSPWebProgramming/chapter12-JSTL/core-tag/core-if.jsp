<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%-- core 태그 임포트 --%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<html>
<head>
    <title>if-else 분기 처리</title>
<head>
<body>

<h4>test="true"</h4>
<c:if test="true">
test="true" : 항상 실행 <br>
</c:if>
<hr>

<h4>test="false"</h4>
<c:if test="false">
test="false" : 항상 실행 x<br>
</c:if>
<hr>

<h4>test="EL"</h4>
<c:if test="${param.name == 'yj'}">
Nice param : name=yj
</c:if>
<hr>

<h4>test="EL"</h4>
<c:if test="${param.age > 18 }">
Nice param : age(${param.age}) > 18
</c:if>
<hr>

</body>
</html>