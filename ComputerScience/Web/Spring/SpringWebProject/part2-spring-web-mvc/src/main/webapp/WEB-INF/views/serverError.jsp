<%--
  Created by IntelliJ IDEA.
  User: yjchoi
  Date: 22. 2. 1.
  Time: 오후 9:42
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<html>
<head>
    <title>Server Internal Error</title>
</head>
<body>
<h1>Server Error!</h1>
<h4><c:out value="${error.getMessage()}"></c:out></h4>

<ul>
    <c:forEach var="stack" items="${error.getStackTrace()}">
        <li>
            <c:out value="${stack}"></c:out>
        </li>
    </c:forEach>
</ul>
</body>
</html>
