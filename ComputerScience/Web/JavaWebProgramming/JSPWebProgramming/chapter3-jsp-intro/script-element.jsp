<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>

<%-- 선언부 : 메서드 작성 --%>
<%! 
    public int multiply(int a, int b) {
        return a*b;
    }
%>

<html>
<head>
    <title>스크립트 요소</title>
<head>
<body>
<%-- 스크립틀릿 --%>
<% 
    int sum1 = 0;
    for(int i=1;i<=10;i++){
        sum1 = sum1 + i;
    }
%>
<% 
    int sum2 = 0;
    for(int i=1;i<=100;i++){
        sum2 = sum2 + i;
    }
%>
<%
    int multiplyRet = multiply(11, 12);
%>



<h1>스크립트 요소 3가지</h1>
<ul>
    <li>스크립트릿</li>
    <li>표현식</li>
    <li>선언부</li>
</ul>

<h2>스크립틀릿 예제</h2>
<p>Sum of 1 ~ 10 : <%= sum1 %></p>
<p>Sum of 1 ~ 100 : <%= sum2 %></p>

<h2>선언부 예제</h2>
<p>10 * 17 = <%= multiply(10, 17) %></p>
<p>Result from scriptlet : <%= multiplyRet %> </p>
    
</body>
</html>