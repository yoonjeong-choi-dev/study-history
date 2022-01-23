<%@ page language="java" contentType="text/html; charset=UTF-8" %>

<html>
<head>
    <title>회원 정보</title>
</head>

<body>
<jsp:include page="/view/Header.jsp" />

<h1>회원 정보</h1>
<form action='update.do' method='post'>
    번호: <input type='text' name='id' value='${member.id}' readonly> <br>
    이름: <input type='text' name='name' value='${member.name}'> <br>
    이메일: <input type='text' name='email' value='${member.email}'> <br>
    가입일: ${member.createdDate}<br>
    <input type='submit' value='저장'>
    <input type='button' value='삭제' onclick='location.href="delete.do?id=${member.id}";'>
    <input type='button' value='취소' onclick='location.href="list.do"'>
</form>

<jsp:include page="/view/Tail.jsp" />
</body>
</html>