<%--
  Created by IntelliJ IDEA.
  User: yjchoi
  Date: 22. 2. 1.
  Time: 오후 8:41
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Binding Form</title>
</head>
<body>
<form action="post" method="POST">
    <fieldset>
        <legend>Init Binding을 이용한 폼처리</legend>
        <table>
            <tr>
                <td><label for="title1">title</label></td>
                <td><input type="text" name="title" id="title1"></td>
            </tr>
            <tr>
                <td><label for="dueDate1">기한</label></td>
                <td><input type="date" name="dueDate" id="dueDate1"></td>
            </tr>
        </table>
        <input type="submit" value="제출">
    </fieldset>
</form>

<form action="postModelAttribute" method="POST">
    <fieldset>
        <legend>Init Binding을 이용한 폼처리</legend>
        <table>
            <tr>
                <td><label for="page">Page</label></td>
                <td><input type="number" name="page" id="page"></td>
            </tr>
            <tr>
                <td><label for="title1">title</label></td>
                <td><input type="text" name="title" id="title2"></td>
            </tr>
            <tr>
                <td><label for="dueDate1">기한</label></td>
                <td><input type="date" name="dueDate" id="dueDate2"></td>
            </tr>
        </table>
        <input type="submit" value="제출">
    </fieldset>
</form>
</body>
</html>
