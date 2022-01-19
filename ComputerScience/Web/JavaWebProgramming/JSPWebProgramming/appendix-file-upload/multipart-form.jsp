<%@ page contentType="text/html; charset=UTF-8" %>
<%@ page trimDirectiveWhitespaces="true" %>

<html>
<head>
    <title>파일 업로드 테스트</title>
<head>
<body>
<h1>파일 업로드 폼</h1>
<form action="multipart-data.jsp" method="POST" enctype="multipart/form-data">
text data : <input type="text" name="text"/> <br>
file date : <input type="file" name="file"/> <br>
<input type="submit" value="파일 전송">
</form>
</body>
</html>