<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt" %>

<%@include file="../includes/header.jsp" %>

<div class="row">
  <div class="col-lg-12">
    <h1 class="page-header">Board Detail</h1>
  </div>
</div>

<div class="row">
  <div class="col-lg-12">
    <div class="panel panel-default">
      <div class="panel-heading">Board Detail Page</div>
      <div class="panel-body">

        <div class="form-group">
          <label>Board ID</label>
          <input class="form-control" name="id" value='<c:out value="${board.id}" />' readonly/>
        </div>

        <div class="form-group">
          <label>Title</label>
          <input class="form-control" name="title" value='<c:out value="${board.title}" />' readonly/>
        </div>

        <div class="form-group">
          <label>Content</label>
          <textarea class="form-control" name="content" rows="3" readonly><c:out value="${board.content}" />
          </textarea>
        </div>

        <div class="form-group">
          <label>Writer</label>
          <input class="form-control" name="writer" value='<c:out value="${board.writer}" />' readonly/>
        </div>

<%--        <button data-oper="modify" class="btn btn-default" onclick="location.href='/board/modify?id=<c:out value="${board.id}" />'">Modify</button>--%>
<%--        <button data-oper="list" class="btn btn-info" onclick="location.href='/board/list'" >List</button>--%>

        <button data-oper='modify' class="btn btn-default">Modify</button>
        <button data-oper='list' class="btn btn-info">List</button>

        <form id='btnForm' action="/board/modify" method="get">
          <input type='hidden' id='id' name='id' value='<c:out value="${board.id}"/>'>
          <input type="hidden" name="pageNum" value='<c:out value="${cri.pageNum}"/>'>
          <input type="hidden" name="numContents" value='<c:out value="${cri.numContents}"/>'>
        </form>

      </div>
    </div>
  </div>
</div>

<script type="text/javascript">
    document.addEventListener("DOMContentLoaded", () => {
        let formObj = document.getElementById("btnForm");

        const modifyBtn = document.querySelector("button[data-oper='modify']");
        const listBtn = document.querySelector("button[data-oper='list']");

        modifyBtn.addEventListener('click', (e) => {
            formObj.setAttribute("action", "/board/modify");
            formObj.submit();
        });

        listBtn.addEventListener('click', (e) => {
            const hidden = formObj.querySelector('#id');
            if (!hidden)
              hidden.parentNode.removeChild(hidden);

            formObj.setAttribute("action", "/board/list");
            formObj.submit();
        });

    })

</script>

<%@include file="../includes/footer.jsp" %>