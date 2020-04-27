(function() {
    const fruitsTableElement = $("#fruits-table");
    const sortableFruitsTable = new SortableTable(fruitsTableElement);

    const rotateTableButton = $("#rotate-fruits-table");
    rotateTableButton.click(() => {
        sortableFruitsTable.rotateTable();
    });

    const numberSort = (a, b) => a - b;

    const fruitsTablePriceHeaderElement = $("#fruits-table-price-header");
    sortableFruitsTable.setCellSortFunction(fruitsTablePriceHeaderElement, numberSort);

    const fruitsTableQuantityHeaderElement = $("#fruits-table-quantity-header");
    sortableFruitsTable.setCellSortFunction(fruitsTableQuantityHeaderElement, numberSort);
})();
