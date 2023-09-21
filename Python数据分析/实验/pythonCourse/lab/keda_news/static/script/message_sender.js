let messageBoxCounter = 0;
function showMessage(message, type, animationTime = -1, stopTime = -1, debugMode = false, topPosition = -1) {
    
    if(messageBoxCounter === 0){
        let defaultStyle = document.createElement('style');
        defaultStyle.textContent = '.message{box-shadow: 1px 1px 10px #bbb;border-radius: 0.3em;position: fixed; z-index: 999; padding: 0.2em;max-width: 80%;width: max-content;margin: 0 auto;right: 0;left: 0;display: flex;}.message svg{height: 1.3em;align-self: center;flex-shrink: 0;}.message p{align-self: center;font-size: 1.3em;margin: 0 0.3em;}.success{border: 1px solid #a0ffa0;background-color: #c0ffc0;}.failed{border: 1px solid hotpink;background-color: pink;}.notice{border: 1px solid #bfc780;background-color: gold;}';
        let styleId = document.createAttribute('styleId');
        styleId.nodeValue = 'message_sender_default';
        defaultStyle.attributes.setNamedItem(styleId);
        document.head.appendChild(defaultStyle);
    }
    let colors = ['success', 'failed', 'notice'];
    for (let i = 0; i < colors.length; i++) {
        if(type === colors[i]){
            break
        }else {
            if(i === colors.length-1){
                
            }else {
                continue;
            }
        }
        type = 'failed';
    }
    let symbols = {
        'success': '<path d="M511.998465 65.290005c-246.722194 0-446.708971 200.001103-446.708971 446.708971 0 246.708891 199.986777 446.709995 446.708971 446.709995 246.708891 0 446.711018-200.001103 446.711018-446.709995C958.709483 265.291109 758.707356 65.290005 511.998465 65.290005L511.998465 65.290005zM756.308727 405.884171 465.103412 697.081299c-6.804986 6.819313-17.856693 6.819313-24.662703 0L267.69025 524.33084c-6.804986-6.804986-6.804986-17.856693 0-24.668843l54.29765-54.290487c6.804986-6.812149 17.856693-6.812149 24.662703 0l106.122993 106.107643 224.574778-224.561475c6.804986-6.812149 17.857716-6.812149 24.663726 0l54.29765 54.290487C763.128039 388.020314 763.128039 399.072021 756.308727 405.884171L756.308727 405.884171 756.308727 405.884171zM756.308727 405.884171" fill="#3CB371"></path>',
        'failed': '<path d="M511.999488 65.290005C265.29162 65.290005 65.290517 265.291109 65.290517 511.998977c0 246.708891 200.001103 446.709995 446.708971 446.709995S958.70846 758.707868 958.70846 511.998977C958.70846 265.291109 758.707356 65.290005 511.999488 65.290005L511.999488 65.290005zM716.82855 637.854383c6.803963 6.819313 6.803963 17.856693 0 24.676006l-54.298673 54.29765c-6.819313 6.804986-17.85567 6.820336-24.676006 0L511.999488 590.973656 386.144082 716.828039c-6.819313 6.804986-17.871019 6.804986-24.676006 0l-54.29765-54.29765c-6.804986-6.804986-6.804986-17.856693 0-24.676006l125.869732-125.855406L307.170426 386.144594c-6.804986-6.819313-6.804986-17.871019 0-24.676006l54.29765-54.298673c6.820336-6.803963 17.856693-6.803963 24.676006 0l125.855406 125.870756 125.854383-125.870756c6.820336-6.803963 17.856693-6.803963 24.676006 0l54.298673 54.298673c6.803963 6.804986 6.803963 17.856693 0 24.676006L590.973144 511.998977 716.82855 637.854383 716.82855 637.854383zM716.82855 637.854383" fill="#FF696A"></path>',
        'notice': '<path d="M510.65 962C264.6 962 63.3 760.26 63.3 513.7S264.6 65.41 510.65 65.41 958 267.14 958 513.7 756.69 962 510.65 962zM655 857.61a377.28 377.28 0 0 0 198.65-199.12 371.82 371.82 0 0 0 0-289.58A377.18 377.18 0 0 0 655 169.79a369.15 369.15 0 0 0-288.64 0 377.09 377.09 0 0 0-198.71 199.12 371.82 371.82 0 0 0 0 289.58A377.12 377.12 0 0 0 366.33 857.6a369.21 369.21 0 0 0 288.64 0z" fill="#f4ea2a"></path><path d="M474 662m0-37.5l0-338q0-37.5 37.5-37.5l0 0q37.5 0 37.5 37.5l0 338q0 37.5-37.5 37.5l0 0q-37.5 0-37.5-37.5Z" fill="#f4ea2a"></path><path d="M514.5 741.5m-37.5 0a37.5 37.5 0 1 0 75 0 37.5 37.5 0 1 0-75 0Z" fill="#f4ea2a"></path>'
    }
    let messageBox = document.createElement("div");
    messageBox.innerHTML = '<svg class="icon" viewBox="0 0 1024 1024">'+symbols[type]+'</svg><p>'+message+'</p>'
    messageBox.classList.add('message', type, );
    document.body.append(messageBox);
    messageBox.style.opacity = "0";
    let top = -100;
    let opacity = 0;
    let progress = 0;
    const duration = animationTime === -1 ? 1500 : animationTime;
    const timeWait = stopTime === -1 ? 2000 : stopTime;
    topPosition = topPosition === -1 ? 1/5 : topPosition;
    const interval = 10;
    function calculate() {
        let sine = Math.sin(progress * Math.PI / 2);
        top = -100 + sine * (window.innerHeight * topPosition + 100);
        opacity = Math.pow(Math.sin(progress * Math.PI/2), 2);
    }
    function update() {
        messageBox.style.top = top + "px";
        messageBox.style.opacity = opacity;
    }

    function next() {
        progress += interval / duration;
        return !(progress > 1 && progress < 2);
    }
    function enter() {
        calculate();
        update();
        if (next()) {
            setTimeout(enter, interval);
        } else {
            if(debugMode){
                return;
            }
            setTimeout(exit, timeWait);
        }
    }
    function exit() {
        calculate();
        update();
        if (!next()) {
            setTimeout(exit, interval);
        } else {
            document.body.removeChild(messageBox);
            messageBoxCounter += -1;
            if(messageBoxCounter === 0){
                document.head.querySelector('style[styleId="message_sender_default"]').remove();
            }
        }
    }
    messageBoxCounter += 1;
    enter();
}