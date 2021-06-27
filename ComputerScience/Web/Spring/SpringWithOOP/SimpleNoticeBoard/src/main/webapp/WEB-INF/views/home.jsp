<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jstl/core_rt"%>
<html>
<head>
	<title>Home</title>
</head>
<body>
<h1>
	This is My First Spring Web Service!  
</h1>

<P>  The time on the server is ${serverTime}. </P>
<a href="<c:url value="/board/list" />">게시판 이동</a>
</body>
</html>
