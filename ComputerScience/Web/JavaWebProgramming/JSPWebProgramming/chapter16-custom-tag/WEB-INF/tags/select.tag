<%@ tag body-content="empty" pageEncoding="utf-8" %>
<%@ tag trimDirectiveWhitespaces="true"%>

<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<%-- 속성으로 받을 정적/동적 변수들 정의 --%>
<%@ attribute name="name" required="true" %>
<%@ tag dynamic-attributes="optionMap" %>

<select name="${name}">
    <c:forEach items="${optionMap}" var="option">
        <option value="${option.key}">${option.value}</option>
    </c:forEach>
</select>