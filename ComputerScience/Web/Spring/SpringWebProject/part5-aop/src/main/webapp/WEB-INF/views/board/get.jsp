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
          <textarea class="form-control" name="content" rows="3" readonly><c:out value="${board.content}"/>
          </textarea>
        </div>

        <div class="form-group">
          <label>Writer</label>
          <input class="form-control" name="writer" value='<c:out value="${board.writer}" />' readonly/>
        </div>

        <button data-oper='modify' class="btn btn-default">Modify</button>
        <button data-oper='list' class="btn btn-info">List</button>

        <form id='btnForm' action="/board/modify" method="get">
          <input type='hidden' id='id' name='id' value='<c:out value="${board.id}"/>'>
          <input type="hidden" name="pageNum" value='<c:out value="${cri.pageNum}"/>'>
          <input type="hidden" name="numContents" value='<c:out value="${cri.numContents}"/>'>

          <!-- 검색을 통해 진입한 경우, 검색에 대한 정보 저장 필요 -->
          <input type="hidden" name="type" value='<c:out value="${cri.type}"/>'>
          <input type="hidden" name="keyword" value='<c:out value="${cri.keyword}"/>'>
        </form>

      </div>
    </div>
  </div>
</div>

<!-- Reply Layout -->
<div class="row">
  <div class="col-lg-12">

    <div class="panel panel-default">
      <div class="panel-heading">
        <i class="fa fa-comments fa-fw"></i> Reply
        <button id="registerReplyBtn" class="btn btn-primary btn-xs pull-right">Register Reply</button>
      </div>

      <div class="panel-body">
        <ul class="chat" id="replyLayout">
          <!-- Ajax Call for fetching reply data-->
        </ul>
      </div>

      <div class="panel-footer" id="replyPaging">
        <!-- pagination -->
      </div>

    </div>

  </div>
</div>


<!-- 댓글 추가 Modal 추가 -->
<div id="replyModal" class="modal fade" tabindex="-1" role="dialog"
     aria-labelledby="replyModalLabel" aria-hidden="true">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
        <h4 class="modal-title" id="myModalLabel">Reply Modal</h4>
      </div>
      <div class="modal-body">
        <div class="form-group">
          <label>Reply</label>
          <input class="form-control" name="reply" placeholder="댓글을 입력하세요"/>
        </div>

        <div class="form-group">
          <label>Replier</label>
          <input class="form-control" name="replier" placeholder="작성자"/>
        </div>

        <div class="form-group">
          <label>Reply Date</label>
          <input class="form-control" name="modifiedDate" value="" readonly/>
        </div>

      </div>
      <div class="modal-footer">
        <button type="button" id="modalModifyBtn" class="btn btn-warning" data-dismiss="modal">Modify</button>
        <button type="button" id="modalRemoveBtn" class="btn btn-danger" data-dismiss="modal">Remove</button>
        <button type="button" id="modalRegisterBtn" class="btn btn-default" data-dismiss="modal">Register</button>
        <button type="button" id="modalCloseBtn" class="btn btn-default" data-dismiss="modal">Close</button>
      </div>
    </div>
  </div>
</div>

<script type="text/javascript" src="/resources/js/utils.js"></script>
<script type="text/javascript" src="/resources/js/reply.js"></script>
<script type="text/javascript">

    let currentReplyPage =1;
    let totalCount = 0;
    const boardId = '<c:out value="${board.id}"/>';

    // 모달은 제이쿼리 이용
    let modalJquery;

    document.addEventListener("DOMContentLoaded", () => {
        modalJquery = $('#replyModal');
        addBoardEvent();

        fetchReplies();

        // 모달 버튼 이벤트
        addModalButtonEvent();

        // 댓글 입력 모달
        onClickRegisterButton();
    });

    function addBoardEvent() {
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
    }

    function fetchReplies() {
        const container = document.getElementById('replyLayout');

        const modalInputReply = modalJquery.find("input[name='reply']");
        const modalInputReplier = modalJquery.find("input[name='replier']");
        const modalInputReplyDate = modalJquery.find("input[name='modifiedDate']");

        const makeReply = (reply) => {
            const ret = document.createElement("div");
            ret.innerHTML = `
              <li class="left clearfix" data-id="\${reply.id}">
                <div>
                  <div class="header">
                    <strong class="primary-font">\${reply.replier}</strong>
                    <small class="pull-right text-muted">\${utils.displayTime(reply.modifiedDate)}</small>
                  </div>
                  <p>\${reply.reply}</p>
                </div>
              </li>
             `;

            ret.addEventListener('click', (e) => {
                replyApi.get(reply.id, (result) => {
                    modalInputReply.val(result.reply);
                    modalInputReplier.val(result.replier);
                    modalInputReplyDate.val(utils.displayTime(result.modifiedDate)).attr('readonly', 'readonly');
                    modalJquery.data('id', reply.id);

                    // 관련 없는 버튼 삭제
                    modalJquery.find("#modalRegisterBtn").hide();

                    // 등록 버튼 보이기
                    modalJquery.find("#modalModifyBtn").show();
                    modalJquery.find("#modalRemoveBtn").show();

                    // 모달 띄우기
                    modalJquery.modal('show');
                })
            });

            return ret;
        }

        const fetchCallback = (numReplies, replies) => {
            totalCount = numReplies;
            // -1인 경우 마지막 페이지로 이동
            if (currentReplyPage === -1) {
                currentReplyPage = Math.ceil(numReplies / 10.0);
                fetchReplies();
                return;
            }

            container.innerHTML = "";
            if (replies == null || replies.length === 0) {
                return;
            }

            replies.forEach(reply => {
                container.appendChild(makeReply(reply));
            });

            // pagination
            showReplyPage();
        }

        const param = {
            boardId,
            page: currentReplyPage || 1,
        };

        replyApi.getList(param, fetchCallback);
    }

    function addModalButtonEvent() {
        let modalModifyBtn = modalJquery.find("#modalModifyBtn");
        let modalRemoveBtn = modalJquery.find("#modalRemoveBtn");
        let modalRegisterBtn = modalJquery.find("#modalRegisterBtn");

        modalJquery.find('#modalCloseBtn').on('click', (e) => {
            modalJquery.modal('hide');
        });


        modalRegisterBtn.on('click', (e) => {
            let reply = modalJquery.find("input[name = 'reply']").val();
            let replier = modalJquery.find("input[name = 'replier']").val();

            let payload = {reply, replier, boardId};

            replyApi.register(payload, (result) => {
                modalJquery.find("input").val("");
                modalJquery.modal('hide');
                currentReplyPage = -1;
                fetchReplies();
            })
        });

        modalModifyBtn.on('click', (e) => {
            let reply = modalJquery.find("input[name = 'reply']").val();
            let payload = {
                id: modalJquery.data('id'),
                reply
            };

            replyApi.update(payload, (result) => {
                modalJquery.modal('hide');
                fetchReplies();
            });
        });

        modalRemoveBtn.on('click', (e) => {
            replyApi.remove(modalJquery.data('id'), (result) => {
                modalJquery.modal('hide');
                fetchReplies();
            });
        });
    }

    function onClickRegisterButton() {
        document.getElementById('registerReplyBtn').addEventListener('click', (e) => {
            e.preventDefault();

            // 등록 모달의 폼 관련 태그 초기화
            modalJquery.find('input').val('');

            // 등록 시, 수정 시간 정보는 필요없음
            modalJquery.find("input[name='modifiedDate']").closest('div').hide();

            // 등록과 관련 없는 버튼 삭제
            modalJquery.find(".modal-footer button[id != 'modalCloseBtn']").hide();

            // 등록 버튼 보이기
            modalJquery.find("#modalRegisterBtn").show();

            // 모달 띄우기
            modalJquery.modal('show');
        });

    }

    function showReplyPage() {
        const replyPageFooter = document.getElementById('replyPaging');

        let endPage = Math.ceil(currentReplyPage / 10.0) * 10;
        let startPage = (endPage - 10 + 1 > 0) ? endPage - 10 + 1 : 1;


        let prev = startPage !== 1;
        let next = false;

        if (endPage * 10 >= totalCount) {
            endPage = Math.ceil(totalCount / 10.0);
        }

        if (endPage * 10  < totalCount ) {
            next = true;
        }

        let innerHtml = `<ul class='pagination pull-right'>`;

        if (prev) {
            innerHtml += `
          <li class='page-item'>
              <a class='page-link' href='\${startPage -1}'>Previous</a>
          </li>
          `;
        }

        for (let i = startPage; i <= endPage; i++) {
            let active = currentReplyPage === i ? "active" : "";
            innerHtml += `<li class='page-item \${active}'> <a class='page-link' href='\${i}'>\${i}</a></li>`;
        }

        if (next) {
            innerHtml += `
          <li class='page-item'>
              <a class='page-link' href='\${endPage +1}'>Next</a>
          </li>
          `;
        }

        innerHtml += "</ul>"
        replyPageFooter.innerHTML = innerHtml;

        // a tag event
        const aTags = replyPageFooter.querySelectorAll('a');
        aTags.forEach(aTag => {
            aTag.addEventListener("click", (e) => {
                e.preventDefault();
                let targetPageNum = aTag.getAttribute('href');
                currentReplyPage = parseInt(targetPageNum);
                fetchReplies();
            })
        });

    }

</script>

<script type="text/javascript">
    //console.log("Test Register");
    //registerTest();
    //listTest();
    //removeTest();
    //updateTest();
    //getTest();

    function textResultCallback(result) {
        alert('Result : ' + result);
    }

    function errorAlert(e) {
        alert('Error : ' + e);
    }

    function registerTest() {
        console.log("Register Test");

        const boardId = '<c:out value="${board.id}"/>';
        const testReply = {
            boardId: boardId,
            reply: 'Register Test With Client',
            replier: 'ClientTest',
        }

        replyApi.register(testReply, textResultCallback, errorAlert);
    }

    function listTest() {
        console.log("Get List Test");
        const boardId = '<c:out value="${board.id}"/>';
        const param = {
            boardId,
            page: 1,
        };

        const testCallback = (numReplies, replies) => {
            console.log('Total Count : ' + numReplies);
            replies.forEach(reply => console.log(reply));
        }

        replyApi.getList(param, testCallback, errorAlert);
    }

    function removeTest() {
        console.log('Remove Test');
        const id = 14;

        replyApi.remove(id, textResultCallback, errorAlert);
    }

    function updateTest() {
        console.log('Update Test');
        const boardId = '<c:out value="${board.id}"/>';

        const param = {
            boardId,
            id: 15,
            reply: 'Update after register data'
        };

        replyApi.update(param, textResultCallback, errorAlert);
    }

    function getTest() {
        console.log('Get Test');
        replyApi.get(12, console.log, errorAlert);
    }

</script>

<%@include file="../includes/footer.jsp" %>