<%@ page language="java" contentType="text/html; charset=UTF-8" %>

<html>
<head>
	<title>시스템 오류!</title>
</head>
<body>
<h1>Sorry.....</h1>
<p>요청을 처리하는 중 문제가 발생했습니다. 잠시 후 다시 요청해주세요!</p>
<p>원인 : <%= request.getAttribute("error") %></p>
</body>
</html>