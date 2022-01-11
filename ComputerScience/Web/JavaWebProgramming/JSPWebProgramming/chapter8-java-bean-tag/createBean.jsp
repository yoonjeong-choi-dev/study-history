<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>

<%-- useBean을 이용한 자바빈 객체 생성 --%>
<jsp:useBean id="yjInfo" scope="request" class="member.MemberInfo" />
<%
    yjInfo.setId("yjchoi7166");
    yjInfo.setName("최윤정");
    yjInfo.setEmail("yjchoi7166@gmail.com");
%>

<jsp:forward page="./useBeanObject.jsp"/>