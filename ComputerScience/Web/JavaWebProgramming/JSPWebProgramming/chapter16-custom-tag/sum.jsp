<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>


<%@ taglib prefix="tf" tagdir="/WEB-INF/tags" %>

<html>
<head>
    <title>커스텀 sum 태그</title>
<head>
<body>
<tf:sum begin="1" end="100">
1~100까지의 합 : ${sum}
</tf:sum>

<br>
<tf:sumVar var="result" begin="1" end="100">
1~100까지의 합 : ${result}
</tf:sumVar>

</body>
</html>