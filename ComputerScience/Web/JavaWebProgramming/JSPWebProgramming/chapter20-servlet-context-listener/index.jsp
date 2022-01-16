<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>

<%@ page import = "java.sql.DriverManager" %>
<%@ page import = "java.sql.Connection" %>
<%@ page import = "java.sql.Statement" %>
<%@ page import = "java.sql.ResultSet" %>
<%@ page import = "java.sql.SQLException" %>

<html>
<head>
    <title>서블릿 컨텍스트 리스너</title>
<head>
<body>
<h1>데이터베이스 커넥션 테스트</h1>

<table border="1">
<%
    Connection conn = null;
	Statement stmt = null;
	ResultSet rs = null;

    try {
		String jdbcDriver = "jdbc:apache:commons:dbcp:guestbook";
		String query = "select * from guestbook_message";
		conn = DriverManager.getConnection(jdbcDriver);
		stmt = conn.createStatement();
		rs = stmt.executeQuery(query);
		while(rs.next()) {
%>
   
    <tr>
        <td style="width: 500px">
        메시지 번호: <%= rs.getInt("message_id") %> <br>
        손님 이름 : <%= rs.getString("guest_name") %> <br>
        메시지 : <%= rs.getString("message") %> <br>
        </td>
    </tr>
<%
        }
    } finally {
        if (rs != null) try { rs.close(); } catch(SQLException ex) {}
		if (stmt != null) try { stmt.close(); } catch(SQLException ex) {}
		if (conn != null) try { conn.close(); } catch(SQLException ex) {}
    }
%>
</table>

</body>
</html>