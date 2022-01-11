<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>

<%-- jsp:param 액션 태그를 이용하여 얻은 정보 가져오기--%>
<%
    String name = request.getParameter("name");
    String age = request.getParameter("age");

    if(name == null) {
        name = "Anonymous";
    }
    if (age == null) {
        age = "unknwon";
    }
%>

<h3>Hello~ <%=name%>!</h3>
<h3>Your age is <%=age%>!</h3>
<h3>Query parameters with key "name" </h3>
<ul>
<%
    String[] names = request.getParameterValues("name");
    for(String n : names) {
%>
    <li> <%= n %> </li>
<% } %>