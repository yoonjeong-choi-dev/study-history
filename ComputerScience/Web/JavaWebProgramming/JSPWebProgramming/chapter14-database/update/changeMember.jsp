<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>

<%-- JDBC를 이용한 데이터베이스 연결 --%>
<%@ page import="java.sql.DriverManager" %>
<%@ page import="java.sql.Connection" %>
<%@ page import="java.sql.Statement" %>
<%@ page import="java.sql.SQLException" %>



<%
    // 요청 결과 파싱
    request.setCharacterEncoding("utf-8");

    String member_id = request.getParameter("member_id");
    String name = request.getParameter("name");
    String description = request.getParameter("description");

    int updateCount = 0;
    
    // Step 1 : Load JDBC Driver - Class.forName을 통해 해당 클래스 인스턴스를 구함
    // web.xml을 이용하여 어플리케이션 구동 시 드라이버 로딩
    // Class.forName("com.mysql.jdbc.Driver");

    Connection conn = null;
    Statement stmt = null;

    try {
        // DB 연결 관련 정보 설정
        String jdbcDriver = "jdbc:mysql://localhost:3306/jpa14?" + 
            "useUnicode=true&characterEncoding=utf8";
        String dbUser = "jpadbuser";
        String dbPw = "jpadbuser";

        String query = "update member set name = '"+name+"' "
                    + ", description = '"+description+"' "
                    + "where member_id = '"+ member_id+"'";

        // Step 2. Create Connection
        conn = DriverManager.getConnection(jdbcDriver, dbUser, dbPw);

        // Step 3. Create statement
        stmt = conn.createStatement();

        // Step 4. Execute Query
        updateCount= stmt.executeUpdate(query);

    } catch(SQLException ex) {
        out.println(ex.getMessage());
        ex.printStackTrace();
    } finally {
        // Step 6. Terminate statement
		if (stmt != null) try { stmt.close(); } catch(SQLException ex) {}

        // Step 7. Terminate connection
        if (conn != null) try { conn.close(); } catch(SQLException ex) {}
    }
%>

<html>
<head>
    <title>변경 결과</title>
<head>
<body>
<% if (updateCount > 0) {%>
ID <%= member_id %>의 정보 변경 완료<br>
이름을 <%= name %>로 변경<br>
설명을 <%= description%>로 변경<br>
<% } else {%>
<%= member_id %>에 해당하는 유저가 없음<br>
<% }%>

<a href="<%=request.getContextPath()%>/showAllMemebers.jsp">Show All Members</a> <br>
</body>
</html>