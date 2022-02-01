<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<html>
<head>
    <title>DTO Test</title>
</head>
<body>
<h1>Your query parameters...</h1>
<ul>
    <c:forEach var="id" items="${params}">
        <li>${id}</li>
    </c:forEach>
</ul>
</body>
</html>
