(function() {
    const fruitsTableElement = document.querySelector("#fruits-table");
    const sortableFruitsTable = new SortableTable(fruitsTableElement);

    const rotateTableButton = document.querySelector("#rotate-fruits-table");
    rotateTableButton.addEventListener("click", () => {
        sortableFruitsTable.rotateTable();
    });

    const numberSort = (a, b) => a - b;

    const fruitsTablePriceHeaderElement = document.querySelector("#fruits-table-price-header");
    sortableFruitsTable.setCellSortFunction(fruitsTablePriceHeaderElement, numberSort);

    const fruitsTableQuantityHeaderElement = document.querySelector("#fruits-table-quantity-header");
    sortableFruitsTable.setCellSortFunction(fruitsTableQuantityHeaderElement, numberSort);
})();
