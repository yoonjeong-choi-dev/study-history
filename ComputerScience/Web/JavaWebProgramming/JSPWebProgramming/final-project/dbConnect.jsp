<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>

<%@ page import="jdbc.connection.ConnectionProvider" %>
<%@ page import="java.sql.*" %>


<html>
<head>
    <title>DB 연결 테스트</title>
<head>
<body>
<%
	try (Connection conn = ConnectionProvider.getConnection()) {
		out.println("커넥션 연결 성공함");
	} catch(SQLException ex) {
		out.println("커넥션 연결 실패함 : " + ex.getMessage());
		application.log("커넥션 연결 실패", ex);
	}
%>

</body>
</html>