<%@ page language="java" contentType="text/html; charset=UTF-8" %>

<html>
<head>
    <title>프로젝트 등록</title>
    <style>
    ul {
        padding: 0;
    }

    li {
        list-style: none;
    }

    label {
        float: left;
        text-align: right;
        width: 60px;
        padding-right:10px;
    }
    </style>
</head>

<body>
<jsp:include page="/view/Header.jsp" />
<h1>프로젝트 등록</h1>
<form action='add.do' method='post'>
<ul>
    <li>
    <label for="title">제목</label>
    <input type='text' name='title' id='title'>
    </li>

    <li>
    <label for='content'>내용</label>
    <textarea name='content' id='content' rows='5' cols='40'></textarea>
    </li>

    <li>
    <label for='startDate'>시작일</label>
    <input type='date' name='startDate' id='startDate'>
    </li>

    <li>
    <label for='endDate'>종료일</label>
    <input type='date' name='endDate' id='endDate'>
    </li>

    <li>
    <label for='tags'>태그</label>
    <input type='text' name='tags' id='tags'><br>
    </li>
</ul>
    <input type='submit' value='등록'>
    <input type='reset' value='취소'>
</form>
<jsp:include page="/view/Tail.jsp" />
</body>

</html>