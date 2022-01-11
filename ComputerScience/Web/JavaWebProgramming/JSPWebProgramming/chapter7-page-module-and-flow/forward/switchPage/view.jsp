<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>

<%-- 조건에 따라 페이지를 분기하는 파일--%>
<%
    String code = request.getParameter("code");
    String toUrl = null;

    if(code.equals("A")) {
        toUrl = "./module/a.jsp";
    } else if (code.equals("B")) {
        toUrl = "./module/b.jsp";
    } else if (code.equals("C")) {
        toUrl = "./module/c.jsp";
    }
%>
<jsp:forward page="<%= toUrl %>"/>