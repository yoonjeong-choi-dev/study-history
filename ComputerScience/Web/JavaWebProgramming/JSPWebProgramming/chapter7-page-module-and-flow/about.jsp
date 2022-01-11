<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<html>
<head>
    <title>About</title>
<head>
<body>
    <h1>About 페이지입니다</h1>
    <p>이후 문서는 aboutSub.jsp에서 생성한 페이지</p>
    <jsp:include page="/aboutSub.jsp" flush="false">
        <jsp:param name="name" value="Yoonjeong"/>
        <jsp:param name="age" value="30"/>
    </jsp:include>
</body>
</html>