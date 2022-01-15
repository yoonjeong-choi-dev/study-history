<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>


<html>
<head>
    <title>방명록 수정 폼</title>
<head>
<body>
<h2>방명록 수정하기</h2>
<form action="${pageContext.request.contextPath}/updateMessage.jsp" method="POST">
<input type="hidden" name="messageId" value="${param.messageId}"/>
암호 : <input type="text" name="password"><br>
메시지 : <br><textarea name="message" cols="50" rows="3"></textarea><br>
<input type="submit" value="수정하기">
</form>

</body>
</html>