<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%-- core 태그 임포트 --%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<html>
<head>
    <title>choose 분기 처리</title>
<head>
<body>

<h4>쿼리 파라미터 name 및 age 자유롭게 설정</h4>
<c:choose>
    <c:when test="${param.name == 'yj'}">
        Your name is yj!
    </c:when>
    <c:when test="${param.age > 20}">
        You are adult. Your age is ${param.age} 
    </c:when>
    <c:otherwise>
        name과 age를 제대로 입력해보세요
    </c:otherwise>
</c:choose>

</body>
</html>