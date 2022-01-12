<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%@ page import="util.Thermometer" %>
<%
    // 객체 생성
    Thermometer thermometer = new Thermometer();
    request.setAttribute("thermo", thermometer);
%>
<html>
<head>
    <title>메서드 사용하기</title>
<head>
<body>

<%-- thermo만 입력 시 : page-> request -> session -> application 영역을 차례로 검사하면서 객체 찾음--%>
${thermo.setCelsius("서울", 18.2)}
서울 온도 : ${thermo.getCelsius("서울")}도/ 화씨 : ${thermo.getFahrenheit("서울")}
<br>
정보 :${thermo.info}

</body>
</html>