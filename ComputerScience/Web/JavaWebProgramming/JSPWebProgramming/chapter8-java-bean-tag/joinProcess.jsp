<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>

<%-- 요청 객체 인코딩 설정 --%>
<%
    request.setCharacterEncoding("utf-8");
%>

<%-- useBean을 이용한 자바빈 객체 생성 --%>
<jsp:useBean id="memberInfo" scope="request" class="member.MemberInfo" />
<jsp:setProperty name="memberInfo" property="*" />
<jsp:setProperty name="memberInfo" property="password" value="<%= memberInfo.getId() %>"/>
<html>
<head>
    <title>회원 가입 완료</title>
<head>
<body>

<table width="400" border="1" cellpadding="0" cellspacing="0">
    <tr>
        <td>아이디</td>
        <td>비밀번호</td>
        <td>이름</td>
        <td>이메일</td>
    </tr>

    <tr>
        <td><jsp:getProperty name="memberInfo" property="id"/></td>
        <td><jsp:getProperty name="memberInfo" property="password"/></td>
        <td><jsp:getProperty name="memberInfo" property="name"/></td>
        <td><jsp:getProperty name="memberInfo" property="email"/></td>
    </tr>
</table>
    
</body>
</html>