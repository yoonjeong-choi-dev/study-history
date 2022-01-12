<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%
    // 세션의 속성 접근
    session.setAttribute("memberId", "yjchoi7166");
    session.setAttribute("name", "최윤정이다");
%>
<html>
<head>
    <title>세션 속성 추가</title>
<head>
<body>
<h1>세션 속성을 추가하였습니다</h1>
<h3>추가된 속성은 다음과 같습니다</h3>
<ul>
<%
    String id = (String) session.getAttribute("memberId");
    String name = (String) session.getAttribute("name");
%>
<li> Id : <%= id %> </li>
<li> Name : <%= name %> </li>
</ul>

<a href="<%= request.getContextPath()%>/viewSessionCookie.jsp">세션 속성 확인하기</a>
</body>
</html>