document.addEventListener('DOMContentLoaded', function(){
    const allButtons = document.querySelectorAll('.searchBtn');
    const serachBar = document.querySelector('.searchBar');
    const searchInput = document.getElementById('searchInput');
    const searchClose = document.getElementById('searchClose');


    for(let i = 0; i < allButtons.length; i++){
        allButtons[i].addEventListener('click', function(){
            serachBar.style.visibility = 'visible';
            serachBar.classList.add('open');
            this.setAttribute('aria-expanded', 'true');
            searchInput.focus();
        });
    };


    searchClose.addEventListener('click', function(){
        serachBar.style.visibility = 'hidden';
        serachBar.classList.remove('open');
        this.setAttribute('aria-expanded', 'false');
        searchInput.focus();
    });


});