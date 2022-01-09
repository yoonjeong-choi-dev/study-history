<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<html>
<head>
    <title>Form</title>
<head>
<body>
    <%-- action 속성값 페이지로 전송--%>
    <form action="/jsp-programming/chapter3-jsp-intro/form-action/viewFormParams.jsp" method="GET">
        이름: <input type="text" name="name" size="10"> <br>
        주소: <input type="text" name="address" size="30"> <br>
        좋아하는 동물:
            <input type="checkbox" name="pet" value="dog"> 강아지
            <input type="checkbox" name="pet" value="cat"> 고양이
            <input type="checkbox" name="pet" value="eagle"> 독수리
        <input type="submit" value="전송">
    </form>
</body>
</html>