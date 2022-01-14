<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<html>
<head>
    <title>유저 등록</title>
<head>
<body>
<form action="<%= request.getContextPath()%>/insert/insertMember.jsp" method="POST">
<table border="1">
<tr>
    <td>아이디</td>
    <td><input type="text" name="member_id" size="10"></td>
    <td>이름</td>
    <td><input type="text" name="name" size="10"></td>
</tr>
<tr>
    <td>설명</td>
    <td colspan="3"><input type="text" name="description" size="30"></td>
</tr>
<tr>
    <td colspan="4"><input type="submit" value="Change"/></td>
</tr>
</table>
</form>
    
</body>
</html>