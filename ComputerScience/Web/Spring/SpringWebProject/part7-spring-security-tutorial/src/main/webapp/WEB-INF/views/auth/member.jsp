<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>

<html>
<head>
  <title>Login User</title>
</head>
<body>

<h1>This page can be accessed only by login user</h1>
<h2><c:out value="${message}"/></h2>

<%@include file="authFooter.jsp"%>
</body>
</html>
