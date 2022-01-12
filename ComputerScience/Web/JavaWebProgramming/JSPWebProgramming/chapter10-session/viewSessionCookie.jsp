<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%-- page 디렉티브의 세션 속성 기본값은 true : 세션 사용 --%>
<%-- 세션 사용시, 아래의 page 디렉티브 설정은 생략 가능 --%>
<%@ page session="true" %>

<%@ page import="java.util.Date" %>
<%@ page import="java.text.SimpleDateFormat" %>

<%
    // 세션의 시간 정보 포멧을 위한 변수들
    Date time = new Date();
	SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
    String id = (String) session.getAttribute("memberId");
    String name = (String) session.getAttribute("name");
%>
<html>
<head>
    <title>세션 정보</title>
<head>
<body>
세션 ID : <%= session.getId() %> <br>
<%
    time.setTime(session.getCreationTime());
%>
세션 생성 시간 : <%= formatter.format(time) %> <br>
<%
    time.setTime(session.getLastAccessedTime());
%>
세션 마지막 접근 시간 : <%= formatter.format(time) %> <br>

<% 
    if (id != null) {
%>
Id : <%= id %> <br>
<% } else {%>
No "id" attribute in this session <br>
<% } %>
<%
    if (name !=null) {
%>
Name : <%= name%> <br>
<% } else {%>
No "name" attribute in this session <br>
<% } %>

<a href="<%= request.getContextPath()%>/viewCookies.jsp">세션 확인용 쿠키 보기</a> <br>
<a href="<%= request.getContextPath()%>/setSession.jsp">세션 속성 추가하기</a> <br>
<a href="<%= request.getContextPath()%>/closeSession.jsp">세션 종료</a>
</body>
</html>