<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<html>
<head>
    <title>JSTL 예제</title>
<head>
<body>
<h1>태그 예제들</h1>
<p>Core 태그</p>
<ul>
    <li><a href="<%= request.getContextPath()%>/core-tag/core-set-remove.jsp">set and remove</a></li>
    <li><a href="<%= request.getContextPath()%>/core-tag/core-if.jsp">if-else</a></li>
    <li><a href="<%= request.getContextPath()%>/core-tag/core-choose.jsp">core-choose</a></li>
    <li><a href="<%= request.getContextPath()%>/core-tag/core-foreach.jsp">core-foreach</a></li>
    <li><a href="<%= request.getContextPath()%>/core-tag/core-fortokens.jsp">core-forTokens</a></li>
    <li><a href="<%= request.getContextPath()%>/core-tag/core-url.jsp">core-url</a></li>
    <li><a href="<%= request.getContextPath()%>/core-tag/catch.jsp">catch</a></li>
</ul>
<p>국제화 태그</p>
<ul>
<li>
    <p>fmt:bundle 이용</p>
    <ul>
        <li><a href="<%= request.getContextPath()%>/fmt-tag/fmt-bundle.jsp?id=yjchoi7166">브라우저 언어 : Accept-Language 헤더</a></li>
        <li><a href="<%= request.getContextPath()%>/fmt-tag/fmt-bundle.jsp?id=yjchoi7166&lang=en">영문</a></li>
    </ul>
</li>

<li>
    <p>fmt:setBundle 이용</p>
    <ul>
        <li><a href="<%= request.getContextPath()%>/fmt-tag/fmt-setBundle.jsp?id=yjchoi7166">브라우저 언어 : Accept-Language 헤더</a></li>
        <li><a href="<%= request.getContextPath()%>/fmt-tag/fmt-setBundle.jsp?id=yjchoi7166&lang=en">영문</a></li>
    </ul>
</li>

<li><a href="<%= request.getContextPath()%>/fmt-tag/formatting.jsp">포멧팅</a></li>
    
</ul>
</body>
</html>