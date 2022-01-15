<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>

<%-- 필요한 dao 및 service --%>
<%@ page import="guestbook.service.UpdateMessageService" %>
<%@ page import="guestbook.service.InvalidPassowrdException" %>
<%@ page import="guestbook.service.MessageNotFoundException" %>

<%
    request.setCharacterEncoding("utf-8");

    int messageId = Integer.parseInt(request.getParameter("messageId"));
    String password = request.getParameter("password");
    String message = request.getParameter("message");
    boolean isInvalidPassword  = false;
    boolean isNotFound = false;

    try {
        UpdateMessageService updateService = UpdateMessageService.getInstance();
        updateService.updateMessage(messageId, password, message);
    } catch (InvalidPassowrdException ex) {
        isInvalidPassword = true;
    } catch (MessageNotFoundException ex) {
        isNotFound = true;
    }
%>

<html>
<head>
    <title>방명록 수정</title>
<head>
<body>

<% if (isInvalidPassword) {%>
    입력한 암호가 올바르지 않습니다. 암호를 확인해주세요. <br>
    <a href="${pageContext.request.contextPath}/confimUpdate.jsp?messageId=<%=messageId %>">[암호 다시 입력하기]</a>
<% } else if (isNotFound) {%>
    해당 메시지를 찾지 못했습니다.
<% } else { %>
    메세지를 수정하였습니다
<% }%>
<br>
<a href="${pageContext.request.contextPath}">[목록 보기]</a>

</body>
</html>