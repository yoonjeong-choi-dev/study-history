<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>

<%-- useBean을 이용한 자바빈 객체 접근 --%>
<jsp:useBean id="yjInfo" scope="request" class="member.MemberInfo" />
<html>
<head>
    <title>useBean 태그 예제</title>
<head>
<body>
    아이디 : <%= yjInfo.getId() %> <br>
    이름 : <%= yjInfo.getName() %> <br>
    이메일 : <%= yjInfo.getEmail() %> <br>
</body>
</html>