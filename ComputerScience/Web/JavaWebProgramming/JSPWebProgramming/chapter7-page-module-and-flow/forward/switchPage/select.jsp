<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<html>
<head>
    <title>페이지 옵션</title>
<head>
<body>
    <form action="<%= request.getContextPath() %>/forward/switchPage/view.jsp">
        보고 싶은 페이지 선택
        <select name="code">
            <option value="A">A Page</option>
            <option value="B">B Page</option>
            <option value="C">C Page</option>
        </select>

        <input type="submit" value="이동"/>
    </form>
</body>
</html>