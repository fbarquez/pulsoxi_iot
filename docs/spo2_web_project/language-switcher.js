function switchLanguage(lang) {
    document.querySelectorAll('[data-lang]').forEach(el => {
        el.classList.toggle('hidden', el.getAttribute('data-lang') !== lang);
    });
}

function showSection(id) {
    document.querySelectorAll('.section').forEach(sec => {
        sec.classList.add('hidden');
    });
    document.getElementById(id).classList.remove('hidden');
}
