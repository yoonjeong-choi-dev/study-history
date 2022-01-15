<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>

<%-- 필요한 dao 및 service  --%>
<%@ page import="guestbook.model.Message"%>
<%@ page import="guestbook.service.MessageListView"%>
<%@ page import="guestbook.service.GetMessageListService"%>

<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<%
    String pageNumberStr = request.getParameter("page");
    int pageNumber = 1;
    if (pageNumberStr != null) {
        pageNumber = Integer.parseInt(pageNumberStr);
    }

    GetMessageListService messageListService = GetMessageListService.getInstance();
    MessageListView viewData = messageListService.getMessageList(pageNumber);
%>
<c:set var="viewData" value="<%= viewData %>"/>

<html>
<head>
    <title>방명록 목록</title>
<head>
<body>

<form action="${pageContext.request.contextPath}/writeMessage.jsp" method="POST">
이름 : <input type="text" name="guestName"><br>
암호 : <input type="text" name="password"><br>
메시지 : <br><textarea name="message" cols="50" rows="3"></textarea><br>
<input type="submit" value="방명록 등록"/>
</form>
<hr>

<c:if test="${viewData.isEmpty()}">
등록된 방명록이 없습니다.
</c:if>
<table border="1">
    <%-- 자바빈 객체의 경우 get프로퍼티() 메서드 호출--%>
    <c:forEach var="message" items="${viewData.messageList}">
    <tr>
        <td style="width: 500px">
        메시지 번호: ${message.id} <br>
        손님 이름 : ${message.guestName} <br>
        메시지 : ${message.message} <br>
        <a href="${pageContext.request.contextPath}/confimUpdate.jsp?messageId=${message.id}">[수정]</a>
        <a href="${pageContext.request.contextPath}/confimDelete.jsp?messageId=${message.id}">[삭제]</a>
        </td>
    </tr>
    </c:forEach>
</table>

<c:forEach var="pageNum" begin="1" end="${viewData.pageTotalCount}">
<a href="${pageContext.request.contextPath}/index.jsp?page=${pageNum}">[${pageNum}]</a>
</c:forEach>


</body>
</html>