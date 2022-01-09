<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%-- page 디렉티브 : 에러 페이지 속성 지정 --%>
<%@ page isErrorPage="true" %>
<html>
<head>
    <title>에러 메시지</title>
<head>
<body>
요청 처리 과정에서 에러가 발생하였습니다<br>
<p>
에러 타입 : <%= exception.getClass().getName() %> <br>
에러 메시지 : <b> <%= exception.getMessage() %> </b>
    
</body>
</html>