<%@ page language="java" contentType="text/html; charset=UTF-8" %>

<html>
<head>
    <title>회원 가입</title>
</head>

<body>
<jsp:include page="/view/Header.jsp" />
<h1>회원 가입</h1>
<form action='add' method='post'>
    이름: <input type='text' name='name'><br>
    이메일: <input type='text' name='email'><br>
    암호: <input type='password' name='password'><br>
    <input type='submit' value='가입'>
    <input type='reset' value='취소'>
</form>
<jsp:include page="/view/Tail.jsp" />
</body>

</html>