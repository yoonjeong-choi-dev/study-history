<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt" %>


<%@include file="../includes/header.jsp" %>

<div class="row">
  <div class="col-lg-12">
    <h1 class="page-header">Tables</h1>
  </div>
</div>

<div class="row">
  <div class="col-lg-12">
    <div class="panel panel-default">
      <div class="panel-heading">
        Board List Page
        <button id='regBtn' type="button" class="btn btn-xs pull-right">Register
          New Board</button>
      </div>

      <div class="panel-body">
        <table class="table table-striped table-bordered table-hover">
          <thead>
          <tr>
            <th>번호</th>
            <th>제목</th>
            <th>작성자</th>
            <th>작성일</th>
            <th>수정일</th>
          </tr>
          </thead>

          <c:forEach var="board" items="${boardList}">
            <tr>
              <td><c:out value="${board.id}" /> </td>
              <td>
<%--                <a href='/board/get?id=<c:out value="${board.id}"/>'><c:out value="${board.title}" /></a>--%>
                    <a class="moveInfo" href='<c:out value="${board.id}"/>'>
                      <c:out value="${board.title}"/>
                    </a>
              </td>

              <td><c:out value="${board.writer}" /> </td>
              <td><fmt:formatDate value="${board.registeredDate}" pattern="yyyy-MM-dd"/></td>
              <td><fmt:formatDate value="${board.modifiedDate}" pattern="yyyy-MM-dd"/></td>
            </tr>
          </c:forEach>
        </table>

        <!-- Pagination -->
        <div class="pull-right">
          <ul class="pagination">
            <c:if test="${pageMaker.prev}">
              <li class="paginate_button previous"><a href="${pageMaker.startPage - 1}">Previous</a></li>
            </c:if>

            <c:forEach var="num" begin="${pageMaker.startPage}" end="${pageMaker.endPage}">
              <li class="paginate_button ${pageMaker.cri.pageNum == num ? "active" : ""}">
                <a href="${num}">${num}</a>
              </li>
            </c:forEach>

            <c:if test="${pageMaker.next}">
              <li class="paginate_button next"><a href="${pageMaker.endPage + 1}">Next</a></li>
            </c:if>
          </ul>
        </div>

        <form id="actionForm" action="/board/list" method="get">
          <input type="hidden" name="pageNum" value="${pageMaker.cri.pageNum}">
          <input type="hidden" name="numContents" value="${pageMaker.cri.numContents}">
        </form>

        <!-- Modal  추가 -->
        <div id="flashMsgModal" class="modal fade" tabindex="-1" role="dialog"
             aria-labelledby="myModalLabel" aria-hidden="true">
          <div class="modal-dialog">
            <div class="modal-content">
              <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
                <h4 class="modal-title" id="myModalLabel">Modal title</h4>
              </div>
              <div id="flash-message-body" class="modal-body">처리가 완료되었습니다.</div>
              <div class="modal-footer">
                <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
<%--                <button type="button" class="btn btn-primary">Save changes</button>--%>
              </div>
            </div>
          </div>
        </div>

      </div>
    </div>
  </div>
</div>


<script type="text/javascript">
    function onClickRegister() {
        document.getElementById("regBtn").addEventListener("click", (e) => {
            self.location = "/board/register";
        })
    }

    function checkFlashMsg(result) {
        // 브라우저가 히스토리가 없는 경우 모달 창을 보이지 않음
        if (result === '' || history.state) {
            return;
        }

        if (parseInt(result) > 0) {
            document.getElementById("flash-message-body").innerHTML = "게시글 " + parseInt(result) + " 번이 등록되었습니다.";
        }

        $("#flashMsgModal").modal("show");
    }

    function disablePageATag(actionForm) {


      let aTags = document.querySelectorAll(".paginate_button a");
      aTags.forEach(aTag => {
          aTag.addEventListener("click", (e) => {
              e.preventDefault();

              actionForm.querySelector("input[name='pageNum']").value = aTag.getAttribute("href");
              actionForm.submit();
          })
      })
    }

    function onClickTitle(actionForm) {
        let titles = document.querySelectorAll(".moveInfo");
        titles.forEach(title => {
            title.addEventListener("click", (e) => {
                e.preventDefault();

                actionForm.innerHTML += "<input type='hidden' name='id' value='" + title.getAttribute("href") + "'>";
                actionForm.setAttribute("action", "/board/get");
                actionForm.setAttribute("method","get");
                actionForm.submit();
            })
        })
    }

    document.addEventListener("DOMContentLoaded", function(){
        let flashMsg = '<c:out value="${flashMsg}"/>';
        checkFlashMsg(flashMsg);

        // 해당 페이지에서는 브라우저 히스토리 스택을 초기화
        history.replaceState({}, null, null);

        onClickRegister();

        let actionForm = document.getElementById("actionForm");
        disablePageATag(actionForm);
        onClickTitle(actionForm);
    });

</script>

<%@include file="../includes/footer.jsp" %>