<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<html>
<head>
    <title>Layout1</title>
<head>
<body>

<table width="400" border="1" cellpadding="0" cellspacing="0">
<tr>
    <td colspan="2">
        <jsp:include page="/modules/top.jsp" flush="false" />
    </td>
</tr>

<tr>
    <td width="100" valign="top">
        <jsp:include page="/modules/left.jsp" flush="fasle" />
    </td>
    <td width="300" valign="top">
        레이아웃 1
        <br><br><br>
    </td>
</tr>

<tr>
    <td colspan="2">
        <jsp:include page="/modules/bottom.jsp" flush="false" />
    </td>
</tr>
</table>

</body>
</html>