<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>

<%@ page import="java.net.URLEncoder" %>
<%
// /etc/hosts 파일의 로컬 호스트 이름으로 dev.yj.com 설정
    Cookie subdomain = new Cookie("subdomain", "yj.com");
    subdomain.setDomain("yj.com");
    subdomain.setPath("/");
    response.addCookie(subdomain);

    Cookie defaultDomain = new Cookie("default", "dev.yj.com");
    defaultDomain.setPath("/");
    response.addCookie(defaultDomain);

    Cookie invalidDomain = new Cookie("invalid", "naver.com");
    invalidDomain.setPath("/");
    invalidDomain.setDomain("naver.com");
%>
<html>
<head>
    <title>쿠키 도메인 설정</title>
<head>
<body>
다음과 같은 쿠키 생성 <br>
<%= subdomain.getName() %> = <%= subdomain.getValue()%> [<%= subdomain.getDomain()%>]<br>
<%= defaultDomain.getName() %> = <%= defaultDomain.getValue()%> [<%= defaultDomain.getDomain()%>]<br>
<%= invalidDomain.getName() %> = <%= invalidDomain.getValue()%> [<%= invalidDomain.getDomain()%>]<br>

</body>
</html>