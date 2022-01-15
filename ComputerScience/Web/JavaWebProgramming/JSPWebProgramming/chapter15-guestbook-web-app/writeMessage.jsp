<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>

<%-- 필요한 dao 및 service --%>
<%@ page import="guestbook.model.Message"%>
<%@ page import="guestbook.service.WriteMessageService"%>

<%
    request.setCharacterEncoding("utf-8");
%>

<%-- jsp:useBean 액션 태그를 이용하여 요청 파라미터를 바로 메시지 객체로 생성 --%>
<jsp:useBean id="message" class="guestbook.model.Message">
    <jsp:setProperty name="message" property="*"/>
</jsp:useBean>

<%
    WriteMessageService writeService = WriteMessageService.getInstance();
    writeService.write(message);
%>


<html>
<head>
    <title>방명록 등록</title>
<head>
<body>
방명록에 메시지를 남겼습니다.
<a href="${pageContext.request.contextPath}">[목록 보기]</a>

</body>
</html>