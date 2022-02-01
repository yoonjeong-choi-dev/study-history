<%--
  Created by IntelliJ IDEA.
  User: yjchoi
  Date: 22. 2. 1.
  Time: 오전 6:26
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Simple</title>
</head>
<body>
<a href="paramDto?name=YJ&age=30">Request with DTO : /simple/dtoParam?name=YJ&age=30</a> <br>
<a href="paramList?ids=1&ids=2&ids=3">Request with list : paramList?ids=1&ids=2&ids=3</a> <br>
<a href="json">JSON Response</a>
<a href="paramList?id=1">To See Server Error Page</a>
</body>
</html>
