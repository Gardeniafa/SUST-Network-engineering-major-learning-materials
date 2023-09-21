const image_add_handler = (blobInfo, progress) => new Promise((resolve, reject) => {
    // ...
});
function initTinyMCE() {
    tinymce.init({
        selector: '#editor',
        language: 'zh-Hans',
        // ... init tinymce editor
    });
}
function submitData(url, data, success, failed) {
    //...
}
let passage_id = undefined;
function save_passage() {
    // ...
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
        // ...
    });
    let nextBtn = document.getElementById('next-passage');
    nextBtn.addEventListener('click', function () {
        // ...
    })
    totalPassagePageSpan.innerHTML = totalPages.toString();
    currentPassagePageSpan.innerHTML = '1';
    pageSlice(passagesDataList, 1, pageTotalRecordMax);
    if (totalPages === 1) {
        nextBtn.setAttribute('disabled', 'disabled');
    }
    function pageSlice(data, index, size) {
        // ...
    }
    function editPassage(passageId,) {
        // ...
    }
    function deletePassage(passageId) {
        // ...
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
