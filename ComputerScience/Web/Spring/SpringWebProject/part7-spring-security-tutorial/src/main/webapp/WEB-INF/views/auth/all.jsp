<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@ taglib prefix="sec" uri="http://www.springframework.org/security/tags"%>

<html>
<head>
  <title>Public Page</title>
</head>
<body>

<h1>This page can be accessed by anyone</h1>
<%@include file="authFooter.jsp"%>
</body>
</html>
