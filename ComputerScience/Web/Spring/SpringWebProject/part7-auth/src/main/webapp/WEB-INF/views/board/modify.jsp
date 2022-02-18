<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt" %>
<%@ taglib prefix="sec" uri="http://www.springframework.org/security/tags" %>

<%@include file="../includes/header.jsp" %>

<style>
    #uploadResult {
        width: 100%;
        background-color: gray;
    }

    #uploadResult ul {
        display: flex;
        flex-flow: row;
        justify-content: left;
        align-items: center;
        flex-wrap: wrap;
    }

    #uploadResult ul li {
        list-style: none;
        padding: 10px;
        cursor: pointer;
    }

    #uploadResult ul li img {
        width: 100px;
        display: block;
    }

</style>


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
          <input type="hidden" name="${_csrf.parameterName}" value="${_csrf.token}"/>
          <input type="hidden" name="pageNum" value='<c:out value="${cri.pageNum}"/>'>
          <input type="hidden" name="numContents" value='<c:out value="${cri.numContents}"/>'>
          <input type="hidden" name="type" value='<c:out value="${cri.type}"/>'>
          <input type="hidden" name="keyword" value='<c:out value="${cri.keyword}"/>'>

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

          <!-- 사용자와 게시자가 일치하는 경우만 수정/삭제 가능 -->
          <sec:authentication property="principal" var="p"/>
          <sec:authorize access="isAuthenticated()">
            <c:if test="${p.username eq board.writer}">
              <button type="submit" data-oper="modify" class="btn btn-default">Modify</button>
              <button type="submit" data-oper="remove" class="btn btn-danger">Delete</button>
            </c:if>
          </sec:authorize>
          <button type="submit" data-oper="list" class="btn btn-info">List</button>
        </form>
      </div>
    </div>
  </div>
</div>

<!-- file attach -->
<div class="row">
  <div class="col-lg-12">
    <div class="panel panel-default">
      <div class="panel-heading">File Attach</div>
      <div class="panel-body">

        <div class="form-group" id="uploadFileDiv">
          <input type="file" id="uploadInputs" name="uploadFiles" multiple/>
        </div>

        <div id="uploadResult">
          <ul>

          </ul>
        </div>

      </div>
    </div>
  </div>
</div>

<script type="text/javascript">
    const csrfHeaderName = "${_csrf.headerName}";
    const csrfToken = "${_csrf.token}";

    const regex = new RegExp('(.*?)\.(exe|sh|zip|alz)$'); // not allowed extensions
    const maxSize = 5242880;  // 5MB
    const boardId = '<c:out value="${board.id}"/>';

    document.addEventListener("DOMContentLoaded", () => {
        let formObj = document.getElementById("modify-form");
        let buttons = formObj.querySelectorAll('button');

        buttons.forEach(button => {
            button.addEventListener('click', (e) => {
                e.preventDefault();

                let ops = button.dataset.oper;

                if (ops === 'remove') {
                    formObj.setAttribute('action', '/board/remove');
                } else if (ops === 'list') {
                    formObj.setAttribute("action", "/board/list");
                    formObj.setAttribute("method", "get");

                    let pageNumTag = formObj.querySelector("input[name='pageNum']").cloneNode();
                    let numContentsTag = formObj.querySelector("input[name='numContents']").cloneNode();
                    let keywordTag = formObj.querySelector("input[name='keyword']").cloneNode();
                    let typeTag = formObj.querySelector("input[name='type']").cloneNode();

                    formObj.innerHTML = "";
                    formObj.append(pageNumTag);
                    formObj.append(numContentsTag);
                    formObj.append(keywordTag);
                    formObj.append(typeTag);
                } else {
                    const paramList = ['fileName', 'uploadPath', 'uuid']
                    $("#uploadResult ul li").each(function(i, file){

                        paramList.forEach(param => {
                            let input = document.createElement('input');
                            input.type = 'hidden';
                            input.name = `attachFileList[\${i}].\${param}`;
                            input.value = file.dataset[param];
                            formObj.appendChild(input);
                        });

                        let input = document.createElement('input');
                        input.type='number';
                        input.name = `attachFileList[\${i}].isImage`;
                        input.value = file.dataset.isImage;
                        formObj.appendChild(input);
                    });
                }

                formObj.submit();
            });
        });


        fetchAttachFiles();
        addClickEventUploadBtn();드
    });

    function fetchAttachFiles() {
        fetch(`/board/getAttachList?boardId=\${boardId}`)
            .then(res => res.json())
            .then(res => {
                console.log(res);
                showUploadResult(res);
            })
            .catch(err => {
                console.error(err);
            });
    }

    function showUploadResult(result) {

        let uploadResultDiv = document.querySelector('#uploadResult ul');

        result.forEach(data => {
            let li = document.createElement('li');
            li.dataset.uploadPath = data.uploadPath;
            li.dataset.uuid = data.uuid;
            li.dataset.fileName = data.fileName;
            li.dataset.isImage = data.isImage;
            uploadResultDiv.appendChild(li);

            let mainDiv = document.createElement('div');
            li.appendChild(mainDiv);

            let title = document.createElement('span');
            title.innerHTML = data.fileName;
            mainDiv.appendChild(title);

            let deleteBtn = document.createElement('button');
            deleteBtn.innerHTML = "<i class='fa fa-times'></i>";
            deleteBtn.classList.add('btn', 'btn-warning', 'bnt-circle');
            mainDiv.appendChild(deleteBtn);

            mainDiv.appendChild(document.createElement('br'));

            // 데이터에 대한 이미지 추가
            let img = document.createElement('img');
            let filePath, imgSrc;
            if (data.isImage === 1) {
                filePath = encodeURIComponent(data.uploadPath + '/s_' + data.uuid + '_' + data.fileName);
                imgSrc = '../upload/display?fileName=' + filePath;
                li.appendChild(img);

            } else {
                filePath = encodeURIComponent(data.uploadPath + '/' + data.uuid + '_' + data.fileName);
                imgSrc = '/resources/img/attachIcon.png';
            }
            img.src = imgSrc;
            mainDiv.appendChild(img);


            deleteBtn.addEventListener('click', (e) => {
                if (confirm('Remove this file ? ')) {
                    console.log('delete data : ' + filePath);
                    uploadResultDiv.removeChild(li);
                }
            })
        })
    }

    function validateFile(fileName, fileSize) {
        if (fileSize >= maxSize) {
            alert('File Size Over ' + maxSize + 'MB');
            return false;
        }

        if (regex.test(fileName)) {
            alert('Cannot upload this file extension');
            return false;
        }

        return true;
    }

    function addClickEventUploadBtn() {
        const uploadInput = document.getElementById('uploadInputs');
        uploadInput.addEventListener('change', (e) => {
            let formData = new FormData();

            let files = document.getElementById('uploadInputs').files;

            [...files].forEach(file => {
                if (!validateFile(file.name, file.size)) {
                    return;
                }

                // 컨트롤러 매개변수와 일치시켜야 함
                formData.append('uploadFiles', file);
            });

            fetch('/upload/', {
                method: 'POST',
                body: formData,
                headers: {
                    [csrfHeaderName] : csrfToken
                },
            })
                .then(res => res.json())
                .then(result => {
                    showUploadResult(result);
                })
                .catch(e => {
                    console.error(e);
                });
        });
    }
</script>

<%@include file="../includes/footer.jsp" %>