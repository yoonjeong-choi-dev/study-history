<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>


<%@ taglib prefix="tf" tagdir="/WEB-INF/tags" %>



<html>
<head>
    <title>헤더 커스텀 태그</title>
<head>
<body>
<tf:header title="커스텀 헤더 태그입니다" />
<tf:header title="레벨 2" level="2"/>
<tf:header title="${'El with level 3'}" level="3"/>

</body>
</html>