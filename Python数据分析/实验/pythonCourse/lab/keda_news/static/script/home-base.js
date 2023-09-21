let autoSlide = setInterval(function () {
    try{
        document.querySelector('#banner-right-btn').click();
    }catch (e){
        console.log(e);
        clearInterval(autoSlide);
    }
}, 3000);