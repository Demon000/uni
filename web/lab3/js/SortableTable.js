class SortableTableType {
    static UNKNOWN = new SortableTableType(0);
    static VERTICAL = new SortableTableType(1);
    static HORIZONTAL = new SortableTableType(2);

    constructor(value) {
        this.value = value;
    }
}

class SortableTableElement {
    constructor() {
        this.cells = [];
    }

    getCell(index) {
        if (index < 0 || index > this.cells.length) {
            throw new Error("Invalid cell index");
        }

        return this.cells[index];
    }

    getCellIndex(cell) {
        if (!cell) {
            throw new Error("Invalid cell value");
        }

        return this.cells.findIndex(c => c === cell);
    }

    getIndexData(index) {
        return this.getCell(index).innerText;
    }

    getLength() {
        return this.cells.length;
    }

    addCell(cell) {
        this.cells.push(cell);
    }

    addCells(cells) {
        for (const cell of cells) {
            this.addCell(cell);
        }
    }

    buildRow() {
        const rowElement = document.createElement("tr");
        for (const cell of this.cells) {
            rowElement.appendChild(cell);
        }

        return rowElement;
    }
}

class SortableHeaderCellStatus {
    static UNSORTED = new SortableHeaderCellStatus(0, "sort-unsorted", false);
    static ASCENDING = new SortableHeaderCellStatus(1, "sort-ascending", true);
    static DESCENDING = new SortableHeaderCellStatus(2, "sort-descending", true);

    constructor(value, className, isSortable) {
        this.value = value;
        this.className = className;
        this.isSortable = isSortable;
    }

    getNext() {
        switch (this) {
            case SortableHeaderCellStatus.UNSORTED:
                return SortableHeaderCellStatus.ASCENDING;
            case SortableHeaderCellStatus.ASCENDING:
                return SortableHeaderCellStatus.DESCENDING;
            case SortableHeaderCellStatus.DESCENDING:
                return SortableHeaderCellStatus.UNSORTED;
        }
    }
}

class SortableTableHeader extends SortableTableElement {
    constructor() {
        super();

        this.sortFunctions = [];
        this.sortStatus = [];
        this.listener = null;
    }

    addCell(cell) {
        super.addCell(cell);
        cell.addEventListener("click", () => {
            this.onCellClick(cell);
        });
        this.sortFunctions.push(null);
        this.sortStatus.push(SortableHeaderCellStatus.UNSORTED);
    }

    getCellSortFunction(cell) {
        const index = this.getCellIndex(cell);
        return this.sortFunctions[index];
    }

    setCellSortFunction(cell, fn) {
        const index = this.getCellIndex(cell);
        this.sortFunctions[index] = fn;
    }

    getCellSortStatus(cell) {
        const index = this.getCellIndex(cell);
        return this.sortStatus[index];
    }

    setCellSortStatus(cell, newStatus) {
        const index = this.getCellIndex(cell);
        const oldStatus = this.sortStatus[index];
        cell.classList.remove(oldStatus.className);
        cell.classList.add(newStatus.className);

        this.sortStatus[index] = newStatus;
    }

    getSortableCell() {
        return this.cells.find(c => {
            const status = this.getCellSortStatus(c);
            return status.isSortable;
        });
    }

    resetCellSortStatus(cell) {
        this.setCellSortStatus(cell, SortableHeaderCellStatus.UNSORTED);
    }

    resetCellsSortStatus() {
        for (const cell of this.cells) {
            this.resetCellSortStatus(cell);
        }
    }

    toggleCellSortStatus(cell) {
        const oldStatus = this.getCellSortStatus(cell);
        const newStatus = oldStatus.getNext();
        this.resetCellsSortStatus();
        this.setCellSortStatus(cell, newStatus);
        this.listener();
    }

    onCellClick(cell) {
        this.toggleCellSortStatus(cell);
    }

    setListener(listener) {
        this.listener = listener;
    }
}

class SortableTable {
    extractElements() {
        const rowElements = this.tableElement.querySelectorAll("tr");

        for (const rowElement of rowElements) {
            const cellElements = rowElement.querySelectorAll("th, td");
            const dataElements = rowElement.querySelectorAll("td");
            const headerElements = rowElement.querySelectorAll("th");
            const isFirstRow = this.type === SortableTableType.UNKNOWN;
            let type = SortableTableType.UNKNOWN;

            if (headerElements.length === 1 && headerElements[0] === cellElements[0] &&
                dataElements.length !== 0) {
                type = SortableTableType.VERTICAL;
            } else if ((isFirstRow && headerElements.length > 0 && dataElements.length === 0) ||
                (!isFirstRow && headerElements.length === 0 && dataElements.length > 0)) {
                type = SortableTableType.HORIZONTAL;
            }

            if (type === SortableTableType.UNKNOWN || (!isFirstRow && this.type !== type)) {
                throw new Error("Invalid table type." +
                    "For a vertical table type, the first cell of each row must be a header cell, " +
                    "and the rest of the cells must be data cells.\n" +
                    "For a horizontal table type, the first row must only contain header cells, " +
                    "and the rest of the rows must only contain data cells");
            }

            if (type === SortableTableType.VERTICAL) {
                if (isFirstRow) {
                    this.header = new SortableTableHeader();
                    for (const cellElement of dataElements) {
                        this.elements.push(new SortableTableElement());
                    }
                }

                this.header.addCell(headerElements[0]);
                dataElements.forEach((cellElement, index) => {
                    this.elements[index].addCell(cellElement);
                });
            } else if (type === SortableTableType.HORIZONTAL) {
                let element;
                if (isFirstRow) {
                    element = new SortableTableHeader();
                    this.header = element;
                } else {
                    element = new SortableTableElement();
                    this.elements.push(element);
                }

                element.addCells(cellElements);
            }

            this.type = type;
        }
    }

    emptyTable() {
        while (this.tableElement.firstChild) {
            this.tableElement.removeChild(this.tableElement.firstChild);
        }
    }

    populateTable(elements) {
        if (this.type === SortableTableType.VERTICAL) {
            for (let i = 0; i < this.header.getLength(); i++) {
                const rowElement = document.createElement("tr");
                rowElement.appendChild(this.header.getCell(i));
                for (const element of elements) {
                    rowElement.appendChild(element.getCell(i));
                }
                this.tableElement.appendChild(rowElement);
            }
        } else if (this.type === SortableTableType.HORIZONTAL) {
            const headerRowElement = this.header.buildRow();
            this.tableElement.appendChild(headerRowElement);

            for (const element of elements) {
                const rowElement = element.buildRow();
                this.tableElement.appendChild(rowElement);
            }
        }
    }

    sortElementsByCell(elements, cell) {
        if (!cell) {
            return;
        }

        const index = this.header.getCellIndex(cell);
        const fn = this.header.getCellSortFunction(cell);
        if (fn) {
            elements.sort((first, second) => {
                return fn(first.getIndexData(index), second.getIndexData(index));
            });
        } else {
            elements.sort((first, second) => {
                const firstData = first.getIndexData(index).toString();
                const secondData = second.getIndexData(index).toString();
                if (firstData < secondData) {
                    return -1;
                }

                if (secondData < firstData) {
                    return 1;
                }

                return 0;
            });
        }

        const status = this.header.getCellSortStatus(cell);
        if (status === SortableHeaderCellStatus.DESCENDING) {
            return elements.reverse();
        }
    }

    refreshElements() {
        const elements = this.elements.slice();
        const sortableCell = this.header.getSortableCell();
        this.sortElementsByCell(elements, sortableCell);
        this.emptyTable();
        this.populateTable(elements);
    }

    rotateTable() {
        if (this.type === SortableTableType.VERTICAL) {
            this.type = SortableTableType.HORIZONTAL;
        } else if (this.type === SortableTableType.HORIZONTAL) {
            this.type = SortableTableType.VERTICAL
        }

        this.refreshElements();
    }

    setCellSortFunction(cell, fn) {
        this.header.setCellSortFunction(cell, fn);
    }

    onCellSortStatusChanged() {
        this.refreshElements()
    }

    constructor(tableElement) {
        this.tableElement = tableElement;
        this.type = SortableTableType.UNKNOWN;

        this.elements = [];
        this.header = null;
        this.extractElements();
        this.header.setListener(this.onCellSortStatusChanged.bind(this));
    }
}
