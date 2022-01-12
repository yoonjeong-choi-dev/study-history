<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%
    // 테스트용 설정들
    request.setAttribute("name", "최윤정");

    Cookie cookie = new Cookie("name", "Yoonjeong");
    response.addCookie(cookie);
%>
<html>
<head>
    <title>기본 연산자</title>
<head>
<body>
<h2>수치 연산</h2>
"10"+1 = ${"10" + 1} <br>
null + 10 = ${null + 10} <br>
2 / 3= ${2/3} <br>

<hr>
<h2>문자열 연산</h2>
"문자" += "열" += "연결" : ${"문자" += "열" += "연결" }<br>

<hr>
<h2>변수 할당</h2>
${arr= [1,2,3]; ""}
arr[2]=${arr[2]}

<br>
</body>
</html>