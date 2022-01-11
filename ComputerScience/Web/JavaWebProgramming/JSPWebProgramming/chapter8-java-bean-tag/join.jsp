<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<html>
<head>
    <title>회원 가입</title>
<head>
<body>

<%-- 
input의 네임 필드는 자바 빈의 프로퍼티 이름과 동일하게 
 => setProperty 액셕 태그를 더 유용하게 사용하기 위해
 --%>
<form action="<%= request.getContextPath() %>/joinProcess.jsp" method="POST">
<table border="1" cellpadding="0" cellspacing="0">
    <tr>
        <td>아이디</td>
        <td colspan="3">
            <input type="text" name="id" size="10">
        </td>
    </tr>

    <tr>
        <td>이름</td>
        <td><input type="text" name="name" size="10"></td>
        <td>이메일</td>
        <td><input type="text" name="email" size="20"></td>
    </tr>

    <tr>
        <td colspan="4" align="center">
            <input type="submit" value="회원가입">
        </td>
    </tr>

</table>
</form>
    
</body>
</html>