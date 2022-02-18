<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt" %>
<%@ taglib prefix="sec" uri="http://www.springframework.org/security/tags" %>

<%@include file="../includes/header.jsp" %>

<div class="row">
  <div class="col-lg-12">
    <h1 class="page-header">Board Register</h1>
  </div>
</div>

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

<!-- board data -->
<div class="row">
  <div class="col-lg-12">
    <div class="panel panel-default">
      <div class="panel-heading">Board Register</div>
      <div class="panel-body">
        <form id="boardForm" role="form" action="register" method="post">

          <input type="hidden" name="${_csrf.parameterName}" value="${_csrf.token}"/>
          <div class="form-group">
            <label>Title</label>
            <input class="form-control" name="title">
          </div>

          <div class="form-group">
            <label>Content</label>
            <textarea class="form-control" name="content" rows="3"></textarea>
          </div>

          <div class="form-group">
            <label>Writer</label>
            <input class="form-control" name="writer" value='<sec:authentication property="principal.username"/>'
                   readonly>
          </div>

          <button id='registerBtn' type="submit" class="btn btn-default">Submit</button>
          <button type="reset" class="btn btn-default">Reset</button>
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

    let uploadResultDiv;

    document.addEventListener('DOMContentLoaded', function () {
        uploadResultDiv = document.querySelector('#uploadResult ul');


        let formObj = $("form[role='form']");

        $("button[type='submit']").on("click", function (e) {
            e.preventDefault();

            const paramList = ['fileName', 'uploadPath', 'uuid']
            $("#uploadResult ul li").each(function (i, file) {

                paramList.forEach(param => {
                    let input = document.createElement('input');
                    input.type = 'hidden';
                    input.name = `attachFileList[\${i}].\${param}`;
                    input.value = file.dataset[param];
                    formObj.append(input);
                });

                let input = document.createElement('input');
                input.type = 'number';
                input.name = `attachFileList[\${i}].isImage`;
                input.value = file.dataset.isImage;
                formObj.append(input);
            });

            formObj.submit();
        });

        // File Upload Layout
        addClickEventUploadBtn();
    });

    function addClickEventUploadBtn() {


        const uploadInput = document.getElementById('uploadInputs');
        uploadInput.addEventListener('change', (e) => {
            let formData = new FormData();

            let files = document.getElementById('uploadInputs').files;
            console.log(files);

            [...files].forEach(file => {
                if (!validateFile(file.name, file.size)) {
                    return;
                }

                // 컨트롤러 매개변수와 일치시켜야 함
                formData.append('uploadFiles', file);
            });

            fetch('/upload/', {
                method: 'POST',
                headers: {
                    [csrfHeaderName] : csrfToken
                },
                body: formData
            })
                .then(res => res.json())
                .then(result => {

                    console.log(result);
                    showUploadResult(result);
                })
                .catch(e => {
                    console.error(e);
                });
        });
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

    function showUploadResult(result) {

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
                let payload = {
                    fileName: filePath,
                    type: data.isImage === 1 ? 'image' : 'file',
                };

                console.log('delete data : ' + payload.fileName + ' , ', payload.type);

                fetch('/upload/', {
                    method: 'DELETE',
                    body: JSON.stringify(payload),
                    headers: {
                        'Content-Type': 'application/json',
                        [csrfHeaderName] : csrfToken,
                    }
                })
                    .then(res => res.text())
                    .then(ret => {
                        console.log(li.dataset);
                        uploadResultDiv.removeChild(li);
                    });
            })
        })
    }


</script>

<%@include file="../includes/footer.jsp" %>