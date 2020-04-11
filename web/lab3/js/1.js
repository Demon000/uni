function linkMovableSelect(firstSelect, secondSelect) {
    firstSelect.addEventListener("dblclick", event => {
        const element = event.target;
        if (element.tagName.toLowerCase() !== "option") {
            return;
        }

        element.selected = false;
        secondSelect.appendChild(element);
    });
}

function linkSwappableSelects(firstSelect, secondSelect) {
    linkMovableSelect(firstSelect, secondSelect);
    linkMovableSelect(secondSelect, firstSelect);
}

(function() {
    const animalsSelect = document.querySelector("#animals-list");
    const favoriteAnimalsSelect = document.querySelector("#favorite-animals-list");

    linkSwappableSelects(animalsSelect, favoriteAnimalsSelect);
})();
