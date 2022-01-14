<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<html>
<head>
    <title>데이터베이스 연결</title>
<head>
<body>
<h1>데이터베이스 예제</h1>
<a href="<%=request.getContextPath()%>/showAllMemebers.jsp">Show All Members</a>
<br>
<a href="<%=request.getContextPath()%>/showAllMemebersWithPool.jsp">Show All Members With Connection Pool</a>
<br>
<a href="<%=request.getContextPath()%>/update/changeMemberForm.jsp">Change Memeber Info</a>
<br>
<a href="<%=request.getContextPath()%>/insert/insertMemberForm.jsp">Insert Memeber Info</a>
<br>
<hr>
<a href="<%=request.getContextPath()%>/selectWithStream.jsp">Long Varchar stream</a>

</body>
</html>