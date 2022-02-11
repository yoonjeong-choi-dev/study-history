<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
  <title>Upload</title>

  <style>
      #uploadResult {
          width: 100%;
          background-color: gray;
      }

      #uploadResult ul {
          display: flex;
          flex-flow: row;
          justify-content: center;
          align-items: center;
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

      #bigPictureWrapper {
          position: absolute;
          display: none;
          justify-content: center;
          align-items: center;
          top: 0%;
          width: 100%;
          height: 100%;
          background-color: gray;
          z-index: 100;
      }

      #bigPicture {
          position: relative;
          display: flex;
          justify-content: center;
          align-items: center;
      }

      #bigPicture img {
          width: 600px;
      }

  </style>
</head>
<body>

<h1>Upload with Ajax</h1>

<div id="uploadDiv">
  <input type="file" id="uploadInputs" name="uploadFile" multiple>
</div>

<button id="uploadButton" style="margin-top: 10px;">Upload</button>

<div id="uploadResult">
  <ul>

  </ul>
</div>

<div id='bigPictureWrapper'>
  <div id='bigPicture'>
  </div>
</div>
</body>

<script src="https://code.jquery.com/jquery-3.3.1.min.js"
        integrity="sha256-FgpCb/KJQlLNfOu91ta32o/NMZxltwRo8QtmkMRdAu8="
        crossorigin="anonymous"></script>

<script type="text/javascript">
    const regex = new RegExp('(.*?)\.(exe|sh|zip|alz)$'); // not allowed extensions
    const maxSize = 5242880;  // 5MB

    let uploadResultDiv;


    document.addEventListener('DOMContentLoaded', function () {
        uploadResultDiv = document.querySelector('#uploadResult ul');
        addClickEventUploadBtn();
        hideOriginImageDiv();
    });

    function addClickEventUploadBtn() {
        const uploadDiv = document.getElementById('uploadDiv');
        const cloneUploadInput = document.getElementById('uploadInputs').cloneNode();

        const btn = document.getElementById('uploadButton');

        btn.addEventListener('click', (e) => {
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

            fetch('/uploadAjax', {
                method: 'POST',
                body: formData
            })
                .then(res => res.json())
                .then(result => {
                    // 제대로 응답이 온 경우 업로드 레이아웃 초기화
                    uploadDiv.innerHTML = "";
                    uploadDiv.appendChild(cloneUploadInput);

                    console.log(result);
                    showUploadResult(result);
                })
                .catch(e => {
                    console.error(e);
                })
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
        uploadResultDiv.innerHTML = '';
        result.forEach(data => {
            let li = document.createElement('li');
            uploadResultDiv.appendChild(li);

            // 데이터에 대한 이미지 추가
            let img = document.createElement('img');
            let filePath;
            if (data.isImage) {
                filePath = encodeURIComponent(data.uploadPath + '/s_' + data.uuid + '_' + data.fileName);
                li.appendChild(document.createTextNode(data.fileName));
                img.src = '/display?fileName=' + filePath;
                li.appendChild(img);

                img.addEventListener('click', (e) => {
                    showImage(encodeURIComponent(data.uploadPath + '/' + data.uuid + '_' + data.fileName));
                });
            } else {
                filePath = encodeURIComponent(data.uploadPath + '/' + data.uuid + '_' + data.fileName);
                img.src = '/resources/img/attachIcon.png';

                let aTag = document.createElement('a');
                aTag.setAttribute('href', '/download?fileName=' + filePath);
                aTag.appendChild(document.createTextNode(data.fileName));
                aTag.appendChild(img);
                li.appendChild(aTag);
            }

            let deleteDiv = document.createElement('span');
            deleteDiv.innerHTML = 'X';
            li.appendChild(deleteDiv);

            deleteDiv.addEventListener('click', (e) => {
                let payload = {
                    fileName: filePath,
                    type: data.isImage ? 'image' : 'file',
                };

                console.log('delete data : ' + payload.fileName + ' , ', payload.type);

                fetch('/deleteFile', {
                    method: 'POST',
                    body: JSON.stringify(payload),
                    headers: {
                        'Content-Type': 'application/json',
                    }
                })
                    .then(res => res.text())
                    .then(ret => {
                        alert(ret);
                    });
            })
        })
    }

    function hideOriginImageDiv() {
        $("#bigPictureWrapper").on("click", function (e) {
            $("#bigPicture").animate({width: '0%', height: '0%'}, 1000);
            setTimeout(() => {
                $(this).hide();
            }, 1000);
        });
    }

    function showImage(filePath) {
        //alert(filePath);

        $("#bigPictureWrapper").css("display", "flex").show();

        $("#bigPicture")
            .html("<img src='/display?fileName=" + filePath + "'>")
            .animate({width: '100%', height: '100%'}, 1000);
    }

</script>

</html>
