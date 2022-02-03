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

        <form id="modify-form" role="form" action="modify" method="POST">

          <div class="form-group">
            <label>Board ID</label>
            <input class="form-control" name="id" value='<c:out value="${board.id}" />' readonly/>
          </div>

          <div class="form-group">
            <label>Title</label>
            <input class="form-control" name="title" value='<c:out value="${board.title}" />'/>
          </div>

          <div class="form-group">
            <label>Content</label>
            <textarea class="form-control" name="content" rows="3"><c:out value="${board.content}"/>
          </textarea>
          </div>

          <div class="form-group">
            <label>Writer</label>
            <input class="form-control" name="writer" value='<c:out value="${board.writer}" />'/>
          </div>

          <div class="form-group">
            <label>RegDate</label>
            <input class="form-control" name='registeredDate'
                   value='<fmt:formatDate pattern = "yyyy/MM/dd" value = "${board.registeredDate}" />'
                   readonly="readonly">
          </div>

          <div class="form-group">
            <label>Update Date</label>
            <input class="form-control" name='modifiedDate'
                   value='<fmt:formatDate pattern = "yyyy/MM/dd" value = "${board.modifiedDate}" />'
                   readonly="readonly">
          </div>


          <button type="submit" data-oper="modify" class="btn btn-default">Modify</button>
          <button type="submit" data-oper="remove" class="btn btn-danger">Delete</button>
          <button type="submit" data-oper="list" class="btn btn-info">List</button>
        </form>
      </div>
    </div>
  </div>
</div>

<script type="text/javascript">
    document.addEventListener("DOMContentLoaded", () => {
        let formObj = document.getElementById("modify-form");
        let buttons = formObj.querySelectorAll('button');

        buttons.forEach(button => {
            button.addEventListener('click', (e) => {
                e.preventDefault();

                let ops = button.dataset.oper;
                if (ops === 'remove') {
                    formObj.setAttribute('action', '/board/remove');
                } else if(ops === 'list') {
                    // self.location = '/board/list';
                    formObj.setAttribute("action", "/board/list");
                    formObj.setAttribute("method","get");
                }

                formObj.submit();
            })
        })

    })

</script>

<%@include file="../includes/footer.jsp" %>