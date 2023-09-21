// 凯撒密码加密
function caesarEncrypt(str, shift) {
    const uppercaseStr = str.toUpperCase();
    let encrypted = '';

    for (let i = 0; i < uppercaseStr.length; i++) {
        const char = uppercaseStr[i];
        if (char >= 'A' && char <= 'Z') {
            const charCode = (char.charCodeAt(0) - 65 + shift) % 26 + 65;
            encrypted += String.fromCharCode(charCode);
        } else {
            encrypted += char;
        }
    }

    return encrypted;
}

// 凯撒密码解密
function caesarDecrypt(str, shift) {
    const uppercaseStr = str.toUpperCase();
    let decrypted = '';

    for (let i = 0; i < uppercaseStr.length; i++) {
        const char = uppercaseStr[i];
        if (char >= 'A' && char <= 'Z') {
            const charCode = (char.charCodeAt(0) - 65 - shift + 26) % 26 + 65;
            decrypted += String.fromCharCode(charCode);
        } else {
            decrypted += char;
        }
    }

    return decrypted;
}
let pwd = document.getElementById('pwd');
let text = document.getElementById('text');
let cipher = document.getElementById('cipher');
document.getElementById('encode').addEventListener('click', function () {
    cipher.value = caesarEncrypt(text.value, parseInt(pwd.value));
});
document.getElementById('decode').addEventListener('click', function () {
    text.value = caesarDecrypt(cipher.value, parseInt(pwd.value));
});

