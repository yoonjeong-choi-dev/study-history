<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>


<%@ taglib prefix="tf" tagdir="/WEB-INF/tags" %>



<html>
<head>
    <title>커스텀 select 태그</title>
<head>
<body>
모드 설정 :
<tf:select name="mode" white="white mode" dark="Dark mode"/>
<br>
색상 설정 :
<tf:select name="color" red="red" cyan="cyan" black="black"/>

</body>
</html>