<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%-- core 태그 임포트 --%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<html>
<head>
    <title>forTokens 예제</title>
<head>
<body>

<h4>java.util.StringTokenizer와 같은 역할</h4>
<c:forTokens var="color" 
    items="red.orange,yellow,green.cyan.blue.violet"
    delims=",.">
Rainbow : ${color}<br>
</c:forTokens>
</body>
</html>