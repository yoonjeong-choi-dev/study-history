<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>

<%
    java.util.Map<String, String> map = new java.util.HashMap<>();
    map.put("name", "YJ");
    map.put("age", "30");
    request.setAttribute("map", map);
%>
<html>
<head>
    <title>스트림 API</title>
<head>
<body>
<h3>배열의 합 구하기 : [1,2,3,4,5]</h3>
sum([1,2,3,4,5]) = ${arr=[1,2,3,4,5]; sum=arr.stream().sum()} 
<br><hr>

<h3>EL에서 map 컬렉션에 대한 스트림 생성 : entrySet() 우선 호출</h3>
map의 모든 값들 : ${requestScope.map.entrySet().stream().map(elem -> elem.value).toList()}
<br><hr>

<h3>filter : [1,2,3,4,5]에서 짝수 찾기</h3>
모든 짝수 : ${arr=[1,2,3,4,5]; arr.stream().filter(n-> n%2 ==0).toList()}
<br><hr>

<h3>map : [1,2,3,4,5]의 모든 요소 제곱</h3>
제곱 결과 : ${arr=[1,2,3,4,5]; arr.stream().map(n-> n*n).toList()}
<br><hr>

<h3>filter : [1,2,3,4,5] 내림차순 정렬</h3>
정렬 결과 : ${arr=[1,2,3,4,5]; arr.stream().sorted((x1,x2)-> x1<x2? 1: -1).toList()}
<br><hr>

<h3>min + Other 객체 예시</h3>
example1 : ${arr=[11,23,19,7,99]}<br>
${minValue='-'; ""}
${arr.stream().min().ifPresent(x-> (minValue=x))}
min value : ${minValue} 입니다 <br>

example2 : ${arr=[]}<br>
${minValue='empty array'; ""}
${arr.stream().min().ifPresent(x-> (minValue=x))}
min value : ${minValue} 입니다 <br>

<br><hr>

<h3></h3>

<br><hr>

</body>
</html>