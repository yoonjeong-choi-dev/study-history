<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%@ page buffer="1kb" %>
<html>
<head>
    <title>from.jsp</title>
<head>
<body>
    <h1>from.jsp에서 생성한 페이지</h1>
    <h2>버퍼 플러시가 발생하면 to.jsp로 forward 태그가 작동하지 않음</h2>
    <p>500에러와 함께 플러시된 데이터만 출력</p>
<%
    for(int i=0; i<300;i++) {
        out.println(i);
    } 
%>

    <jsp:forward page="/forward/to/to.jsp"/>
</body>
</html>