function clearInputBox() {
    document.querySelector('input[name=user]').value = '';
    document.querySelector('input[name=pwd]').value = '';
}

const inputs = document.querySelectorAll('.u-i-v');
inputs.forEach(input => {
    const hr = input.nextElementSibling;
    let interval = undefined;
    input.addEventListener('focus', () => {
        let wid = 0;
        hr.style.borderBottom = '1px solid #000';
        let speed = 0;
        interval = setInterval(function () {
            wid += speed;
            if (wid > 100) {
                clearInterval(interval);
                hr.style.width = '100%';
            } else {
                hr.style.width = wid.toString() + '%';
            }
            if (wid > 66) {
                speed -= 0.3;
            } else {
                speed += 0.6;
            }
        }, 10)
    });
    input.addEventListener('blur', () => {
        clearInterval(interval);
        hr.style.borderBottom = '1px solid #999';
        hr.style.width = '100%';
    });
});

function checkInputIsNotBlank() {
    let userName = document.querySelector("input[name=user]");
    let pwd = document.querySelector("input[name=pwd]");
    if (userName.value.trim() === '' && pwd.value.trim() === '') {
        showMessage('用户名和密码不能为空', 'failed');
        return false;
    }
    return 1 === 1;
}

function getRandomInt(x, y) {
    if (x === undefined && y === undefined) {
        return Math.random();
    }
    if (y === undefined) {
        y = x;
        x = 0;
    }
    x = Math.ceil(x);
    y = Math.floor(y);
    return Math.floor(Math.random() * (y - x) + x);
}

function callback_179_config1(tencentQzoneBackgroundList) {
    console.log('callback 179 was funcked!');
    document.querySelector('section').style.backgroundImage = 'url("'+tencentQzoneBackgroundList['list'][getRandomInt(tencentQzoneBackgroundList['list'].length)]['bg']+'")';
    console.log('fuck 179 end.');
}
document.querySelector('input[name=pwd]').addEventListener('focus', function (){
    this.type = 'password';
});