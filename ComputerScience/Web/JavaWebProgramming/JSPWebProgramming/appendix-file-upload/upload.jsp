<%@ page contentType="text/html; charset=UTF-8" %>
<%@ page trimDirectiveWhitespaces="true" %>

<html>
<head>
    <title>파일 업로드</title>
<head>
<body>
<h1>파일 업로드 폼</h1>
<form action="${pageContext.request.contextPath}/upload" method="POST" enctype="multipart/form-data">
text : <input type="text" name="text"/> <br>
file : <input type="file" name="file"/> <br>
<input type="submit" value="파일 전송">
</form>
</body>
</html>