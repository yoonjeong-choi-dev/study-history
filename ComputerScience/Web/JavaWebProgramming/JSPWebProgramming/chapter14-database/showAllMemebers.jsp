<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>

<%-- JDBC를 이용한 데이터베이스 연결 --%>
<%@ page import="java.sql.DriverManager" %>
<%@ page import="java.sql.Connection" %>
<%@ page import="java.sql.Statement" %>
<%@ page import="java.sql.ResultSet" %>
<%@ page import="java.sql.SQLException" %>

<html>
<head>
    <title>JDBC 예제</title>
<head>
<body>

<table width="100%" border="1">
<tr>
    <td>아이디</td>
	<td>이름</td>
    <td>비밀번호</td>
    <td>이메일</td>
    <td>설명</td>
</tr>

<%
    // Step 1 : Load JDBC Driver - Class.forName을 통해 해당 클래스 인스턴스를 구함
    // web.xml을 이용하여 어플리케이션 구동 시 드라이버 로딩
    // Class.forName("com.mysql.jdbc.Driver");

    Connection conn = null;
    Statement stmt = null;
    ResultSet rs = null;

    try {
        // DB 연결 관련 정보 설정
        String jdbcDriver = "jdbc:mysql://localhost:3306/jpa14?" + 
            "useUnicode=true&characterEncoding=utf8";
        String dbUser = "jpadbuser";
        String dbPw = "jpadbuser";

        String query = "select * from member order by member_id";

        // Step 2. Create Connection
        conn = DriverManager.getConnection(jdbcDriver, dbUser, dbPw);

        // Step 3. Create statement
        stmt = conn.createStatement();

        // Step 4. Execute Query
        rs= stmt.executeQuery(query);

        // Step 5. Print out the result
        while(rs.next()) {  
%>
<tr>
    <td><%= rs.getString("member_id") %></td>
    <td><%= rs.getString("name") %></td>
    <td><%= rs.getString("password") %></td>
    <td><%= rs.getString("email") %></td>
    <td><%= rs.getString("description") %></td>
</tr>
<%
        }
    } catch(SQLException ex) {
        out.println(ex.getMessage());
        ex.printStackTrace();
    } finally {
        // Step 6. Terminate statement
        if (rs != null) try { rs.close(); } catch(SQLException ex) {}
		if (stmt != null) try { stmt.close(); } catch(SQLException ex) {}

        // Step 7. Terminate connection
        if (conn != null) try { conn.close(); } catch(SQLException ex) {}
    }
%>

</table>
<a href="<%=request.getContextPath()%>/update/changeMemberForm.jsp">Change Memeber Info</a>
</body>
</html>