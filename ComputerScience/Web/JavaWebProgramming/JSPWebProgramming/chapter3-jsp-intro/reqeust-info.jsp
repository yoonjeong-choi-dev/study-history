<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<html>
<head>
    <title>request 객체</title>
<head>
<body>
클라이언트 IP = <%= request.getRemoteAddr() %> <br>
요청 정보 길이 = <%= request.getContentLength() %> <br>
요청 정보 인코딩 = <%= request.getCharacterEncoding() %> <br>
요청정보 컨텐츠 타입 = <%= request.getContentType() %> <br>
요청 프로토콜 = <%= request.getProtocol() %> <br>
요청 전송방식 = <%= request.getMethod() %> <br>
요청 URI = <%= request.getRequestURI() %> <br>
컨텍스트 경로 = <%= request.getContextPath() %> <br>
서버 이름 = <%= request.getServerName() %> <br>
서버 포트 = <%= request.getServerPort() %> <br>
</body>
</html>