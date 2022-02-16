<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>

<html>
<head>
  <title>Login Page</title>
</head>
<body>

<h1>Custom Login Page</h1>
<h2><c:out value="${error}"/></h2>
<h2><c:out value="${logout}"/></h2>

<form method="post" action="/login">
  <div>
    <label for="username">User ID : </label>
    <input name="username" id="username"/>
  </div>
  <div>
    <label for="password">Password : </label>
    <input type="password" name="password" id="password"/>
  </div>

  <div>
    <label for="remember-me">Remember me</label>
    <input type="checkbox" name="remember-me" id="remember-me"/>
  </div>
  <div>
    <input type="submit" value="Login"/>
  </div>

  <input type="hidden" name="${_csrf.parameterName}" value="${_csrf.token}"/>

</form>

</body>
</html>
