<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%-- core 태그 임포트 --%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<html>
<head>
    <title>URL 예제</title>
<head>
<body>

<h4>절대 vs 상대 경로</h4>
절대 경로 : <c:url value="www.naver.com" /><br>
상대 경로 : <c:url value="/core-url.jsp"/><br>
<hr>

<h4>URL 생성</h4>
<c:url var="mypage" value="https://github.com/yoonjeong-choi-dev">
    <c:param name="tab" value="overview"/>
    <c:param name="from" value="2022-01-01"/>
    <c:param name="to" value="2022-01-14"/>
</c:url>
My github info : ${mypage} <br>

</body>
</html>