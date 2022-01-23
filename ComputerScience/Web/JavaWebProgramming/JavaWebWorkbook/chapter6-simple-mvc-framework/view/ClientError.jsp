<%@ page language="java" contentType="text/html; charset=UTF-8" %>

<html>
<head>
	<title>Page Not Found</title>
</head>
<body>
<h1>Page Not Found</h1>
<p>원인 : <%= request.getAttribute("error") %></p>
</body>
</html>