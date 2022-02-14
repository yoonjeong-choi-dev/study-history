<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<html>
<head>
  <title>Logout Page</title>
</head>
<body>

<h1>Custom Logout Page</h1>

<form method="post" action="/customLogout">
  <input type="submit" value="Logout"/>
  <input type="hidden" name="${_csrf.parameterName}" value="${_csrf.token}"/>

</form>

</body>
</html>
