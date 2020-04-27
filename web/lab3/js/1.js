function linkMovableSelect(firstSelect, secondSelect) {
    firstSelect.dblclick(event => {
        if (event.target === event.currentTarget) {
            return;
        }

        const element = $(event.target);
        if (element.prop("tagName").toLowerCase() !== "option") {
            return;
        }

        element.prop("selected", false);
        secondSelect.append(element);
    });
}

function linkSwappableSelects(firstSelect, secondSelect) {
    linkMovableSelect(firstSelect, secondSelect);
    linkMovableSelect(secondSelect, firstSelect);
}

(function() {
    const animalsSelect = $("#animals-list");
    const favoriteAnimalsSelect = $("#favorite-animals-list");

    linkSwappableSelects(animalsSelect, favoriteAnimalsSelect);
})();
