const image_add_handler = (blobInfo, progress) => new Promise((resolve, reject) => {
    const xhr = new XMLHttpRequest();
    xhr.withCredentials = false;
    xhr.open('POST', '/addImage');

    xhr.upload.onprogress = (e) => {
        progress(e.loaded / e.total * 100);
    };
    xhr.onload = () => {
        if (xhr.status === 403) {
            reject({message: 'HTTP Error: ' + xhr.status, remove: true});
            return;
        }
        if (xhr.status < 200 || xhr.status >= 300) {
            reject('HTTP Error: ' + xhr.status);
            return;
        }
        const json = JSON.parse(xhr.responseText);

        if (!json || typeof json.source != 'string') {
            reject('Invalid JSON: ' + xhr.responseText);
            return;
        }
        resolve(json.source);
    };
    xhr.onerror = () => {
        reject('Image upload failed due to a XHR Transport error. Code: ' + xhr.status);
    };
    const formData = new FormData();
    formData.append('img', blobInfo.blob(), blobInfo.filename());
    formData.append('api', 'true');
    formData.append('type', 'easy')
    xhr.send(formData);
});

function initTinyMCE() {
    tinymce.init({
        selector: '#editor',
        language: 'zh-Hans',
        branding: false,
        menubar: false,
        plugins: 'emoticons image codesample table image link save',
        font_family_formats: "微软雅黑='微软雅黑'; 宋体='宋体'; 黑体='黑体'; 仿宋='仿宋'; 楷体='楷体'; 隶书='隶书'; 幼圆='幼圆'; 方正舒体='方正舒体'; 方正姚体='方正姚体'; 等线='等线'; 华文彩云='华文彩云'; 华文仿宋='华文仿宋'; 华文行楷='华文行楷'; 华文楷体='华文楷体'; 华文隶书='华文隶书'; Andale Mono=andale mono,times; Arial=arial; Arial Black=arial black;avant garde; Book Antiqua=book antiqua;palatino; Comic Sans MS=comic sans ms; Courier New=courier new;courier; Georgia=georgia; Helvetica=helvetica; Impact=impact;chicago; Symbol=symbol; Tahoma=tahoma;arial; sans-serif; Terminal=terminal,monaco; Times New Roman=times new roman,times; Trebuchet MS=trebuchet ms; Verdana=verdana;geneva; Webdings=webdings; Wingdings=wingdings",
        statusbar: false,
        toolbar: [
            'bold italic underline strikethrough indent outdent | subscript superscript | alignleft aligncenter alignright alignjustify | lineheight emoticons | image blockquote hr codesample table link unlink',
            'save | undo redo | cut paste pastetext | forecolor backcolor | fontfamily fontsize fontsizeinput blocks |'
        ],
        images_upload_handler: image_add_handler,
        width: '100%',
        height: '90%',
        margin: 0,
        save_onsavecallback: save_passage,
        save_enablewhendirty: false,
        placeholder: '在这里输入正文， 点击左上角按钮保存',
        content_style: `
                img{
                max-width:90%;
                min-width: 10%;
                height: auto;
                }
                .mce-content-body[data-mce-placeholder]:not(.mce-visualblocks)::before {
                color: #3336;
                opacity: 1;
                }
                `,
        convert_urls: false,

    });
}

function submitData(url, data, success, failed) {
    let xhr = new XMLHttpRequest();
    xhr.open("POST", url);
    xhr.setRequestHeader("Content-Type", "application/json");
    xhr.responseType = "json";
    xhr.onload = function () {
        if (xhr.status === 200) {
            success(xhr.response);
        } else {
            failed(xhr.status, xhr.statusText);
        }
    };
    xhr.onerror = function () {
        failed(-1, xhr.error);
    };
    xhr.send(JSON.stringify(data));
}

let passage_id = undefined;

function save_passage() {
    let contentHtml = tinymce.activeEditor.getContent();
    let title = document.querySelector('#news-title').value;
    if (title.trim() === '') {
        showMessage('请拟定标题后再提交', 'failed');
        return false;
    }
    if (contentHtml.trim() === '') {
        showMessage('请输入新闻内容后提交', 'failed');
        return false;
    }
    let data = {
        'title': title,
        'content': contentHtml
    };
    if (passage_id) {
        data['passage_id'] = passage_id;
    }
    submitData('addNews', data, function (response) {
        let retData;
        retData = response;
        if (retData['status'] !== 'success') {
            showMessage(retData['message'], 'failed');
        }
        passage_id = retData['passage_id'];
        showMessage('保存成功', 'success');
    }, function (status, message) {
        showMessage('提交失败：' + message + '(' + status + ')', 'failed')
    })
}

const pageTotalRecordMax = 10;

submitData('getAuthorAlbum', {}, function (response) {
    if (response['status'] !== 'success') {
        showMessage(response['message'], 'failed');
        return;
    }
    tablePageResolveMethod(response);
}, function (status, response) {
    showMessage('获取信息出错：' + response + status, 'failed');
})

function tablePageResolveMethod(queryAuthorAlbumResponse) {
    let passagesDataList = queryAuthorAlbumResponse['passages'];
    let totalPages = Math.ceil(passagesDataList.length / pageTotalRecordMax);
    let totalPassagePageSpan = document.getElementById('total-pages');
    let currentPassagePageSpan = document.getElementById('page-number');
    let previousBtn = document.getElementById('previous-passage');
    previousBtn.addEventListener('click', function () {
        let page = parseInt(currentPassagePageSpan.innerHTML);
        page += -1;
        if (page < 1) {
            previousBtn.setAttribute('disabled', 'disabled');
            return;
        }
        pageSlice(passagesDataList, page, pageTotalRecordMax);
        currentPassagePageSpan.innerHTML = '' + page;
        if (page === 1) {
            previousBtn.setAttribute('disabled', 'disabled');
        }
        if (page === totalPages) {
            nextBtn.setAttribute('disabled', 'disabled');
        }
        if (page < totalPages) {
            nextBtn.removeAttribute('disabled');
        }
    });
    let nextBtn = document.getElementById('next-passage');
    nextBtn.addEventListener('click', function () {
        let page = parseInt(currentPassagePageSpan.innerHTML);
        page += 1;
        if (page > totalPages) {
            nextBtn.setAttribute('disabled', 'disabled');
            return;
        }
        currentPassagePageSpan.innerHTML = '' + page;
        pageSlice(passagesDataList, page, pageTotalRecordMax);
        if (page === totalPages) {
            nextBtn.setAttribute('disabled', 'disabled');
        }
        if (page === 1) {
            previousBtn.setAttribute('disabled', 'disabled');
        }
        if (page > 1) {
            previousBtn.removeAttribute('disabled');
        }
    })
    totalPassagePageSpan.innerHTML = totalPages.toString();
    currentPassagePageSpan.innerHTML = '1';
    pageSlice(passagesDataList, 1, pageTotalRecordMax);
    if (totalPages === 1) {
        nextBtn.setAttribute('disabled', 'disabled');
    }

    function pageSlice(data, index, size) {
        let tableContent = document.querySelector('#passages-tbody');
        let passage_data_list = data.slice((index - 1) * size, index * size);
        let tale_page_html = "";
        for (let i = 0; i < passage_data_list.length; i += 1) {
            tale_page_html += '<tr><td>' + (i + 1) + '</td><td>' + passage_data_list[i]['title'] + '</td><td>' + passage_data_list[i]['time'] + '</td>' +
                '<td>' + '<button class="btn-default edit-btn" value="' + passage_data_list[i]['passage_id'] + '">' + '修改' +
                '</button>' + '</td><td>' + '<button class="btn-danger delete-btn" value="' + passage_data_list[i]['passage_id'] + '">' + '删除' +
                '</button>' + '</td></tr>'
        }
        tableContent.innerHTML = '';
        tableContent.innerHTML = tale_page_html;
    }

    function editPassage(passageId,) {
        try {
            document.querySelector('#list-filed').style.display = 'none';
            let editorFiled = document.querySelector('#editor-filed');
            editorFiled.style.display = 'block';
            editorFiled.style.height = '100%';
            initTinyMCE();
            let passageData = undefined;
            for (let i = 0; i < passagesDataList.length; i += 1) {
                if (passagesDataList[i]['passage_id'] === passageId) {
                    passageData = passagesDataList[i];
                }
            }
            document.querySelector('#news-title').value = passageData['title'];
            passage_id = passageData['passage_id'];
            setTimeout(function () {
                tinymce.activeEditor.setContent(passageData['content']);
                showMessage('载入文章成功，编辑后点击工具栏左下角进行保存', 'success');
            }, 666);
            document.querySelector('.no-margin-bottom').innerHTML = '对新闻文章内容进行修改';
        } catch (e) {
            console.log(e);
            showMessage('载入文章出错啦', 'failed');
        }
    }

    function deletePassage(passageId) {
        submitData('/deletePassage', {
            'passage_id': passageId.trim(),
        }, function (response) {
            if (response['status'] !== 'success') {
                showMessage(response['message'], 'failed');
            } else {
                showMessage('删除所选新闻成功', 'success', 300, 300, false, 1/8);
            }
            setTimeout(function () {
                let deleteIndex = 0;
                for (let i = 0; i < passagesDataList.length; i += 1) {
                    if (passagesDataList[i]['passage_id'] === passageId) {
                        deleteIndex = i;
                        break;
                    }
                }
                passagesDataList.splice(deleteIndex, 1);
                totalPages = Math.ceil(passagesDataList.length / pageTotalRecordMax);
                totalPassagePageSpan.innerHTML = totalPages.toString();
                let page = parseInt(currentPassagePageSpan.innerHTML);
                if (page > totalPages) {
                    page = 1;
                }
                pageSlice(passagesDataList, page, pageTotalRecordMax);
                currentPassagePageSpan.innerHTML = page.toString();
                totalPassagePageSpan.innerHTML = totalPages.toString();
                if (page <= 1) {
                    previousBtn.setAttribute('disabled', 'disabled');
                } else {
                    previousBtn.removeAttribute('disabled');
                }
                if (page >= totalPages) {
                    nextBtn.setAttribute('disabled', 'disabled');
                } else {
                    nextBtn.removeAttribute('disabled');
                }
            }, 100);
        }, function (code, response) {
            showMessage('删除错误：' + response + code, 'failed')
        })
    }

    // event delegate
    function eventHandler(event) {
        let target = event.target;
        if (target.classList.contains("edit-btn")) {
            let value = target.value;
            editPassage(value);
        }
        if (target.classList.contains("delete-btn")) {
            let value = target.value;
            deletePassage(value);
        }
    }

    document.querySelector('#passages-tbody').addEventListener('click', eventHandler);
}
