<%@ page language="java" contentType="text/html; charset=UTF-8" %>

<html>
<head>
    <title>프로젝트 수정</title>
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
<h1>프로젝트 정보</h1>
<form action='update.do' method='post'>
<ul>
    <li>
    <label for="id">번호</label>
    <input type='text' name='id' id='id' value='${project.id}' readonly>
    </li>
    <li>
    <label for="title">제목</label>
    <input type='text' name='title' id='title' value='${project.title}'>
    </li>

    <li>
    <label for='content'>내용</label>
    <textarea name='content' id='content' rows='5' cols='40'>${project.content}</textarea>
    </li>

    <li>
    <label for='startDate'>시작일</label>
    <input type='date' name='startDate' id='startDate' value='${project.startDate}'>
    </li>

    <li>
    <label for='endDate'>종료일</label>
    <input type='date' name='endDate' id='endDate' value='${project.endDate}'>
    </li>

    <li>
    <label for='state'>상태</label>
    <select name='state' id='state'>
        <option value='0' ${project.state == 0? "selected" : ""}>준비</option>
        <option value='1' ${project.state == 1? "selected" : ""}>진행</option>
        <option value='2' ${project.state == 2? "selected" : ""}>완료</option>
        <option value='3' ${project.state == 3? "selected" : ""}>취소</option>
    </select>
    </li>

    <li>
    <label for='tags'>태그</label>
    <input type='text' name='tags' id='tags' value='${project.tags}'><br>
    </li>
</ul>
    <input type='submit' value='수정'>
    <input type='button' value='삭제' onclick='location.href="delete.do?id=${project.id}";'>
    <input type='button' value='취소' onclick='location.href="list.do"'>
</form>
<jsp:include page="/view/Tail.jsp" />
</body>

</html>