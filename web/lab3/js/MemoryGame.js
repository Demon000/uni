class MemoryGameCellState {
    static VISIBLE = 0;
    static SOLVED = 1;
    static SELECTED = 2;
    static HIDDEN = 3;
}

class MemoryGameType {
    static NUMBERS = 0;
    static IMAGES = 1;
}

class MemoryGameCell {
    createElement() {
        const element = document.createElement("td");
        element.classList.add("memory-game-cell");
        element.addEventListener("click", () => {
            this.onClick(this);
        });
        return element;
    }

    createDataElement(data) {
        let dataElement;

        if (this.type === MemoryGameType.NUMBERS) {
            dataElement = document.createElement("p");
            dataElement.innerHTML = data;
        } else if (this.type === MemoryGameType.IMAGES) {
            dataElement = document.createElement("img");
            dataElement.src = data;
        }

        dataElement.classList.add("memory-game-cell-data");

        return dataElement;
    }

    constructor(parentElement, options) {
        this.state = MemoryGameCellState.HIDDEN;
        this.type = options.type;
        this.onClick = options.onClick;

        this.element = this.createElement(parentElement);
        parentElement.appendChild(this.element);
    }

    attachData(data) {
        this.data = data;
        this.dataElement = this.createDataElement(data);
        this.element.appendChild(this.dataElement);
    }

    detachData() {
        if (!this.data) {
            return;
        }

        this.element.removeChild(this.dataElement);
        this.dataElement = null;
        this.data = null;
    }

    setClass(name, enabled) {
        if (enabled) {
            this.element.classList.add(name);
        } else {
            this.element.classList.remove(name);
        }
    }

    setClassForState(state, enabled) {
        switch (state) {
            case MemoryGameCellState.VISIBLE:
                this.setClass("visible", enabled);
                break;
            case MemoryGameCellState.SOLVED:
                this.setClass("solved", enabled);
                break;
            case MemoryGameCellState.SELECTED:
                this.setClass("selected", enabled);
                break;
        }
    }

    setState(state) {
        if (state === this.state) {
            return;
        }

        this.setClassForState(state, true);
        this.setClassForState(this.state, false);

        this.state = state;
    }
}

class MemoryGame {
    createTableElement() {
        const tableElement = document.createElement("table");
        tableElement.classList.add("memory-game-table");
        if (this.type === MemoryGameType.IMAGES) {
            tableElement.classList.add("images");
        } else if (this.type === MemoryGameType.NUMBERS) {
            tableElement.classList.add("numbers");
        }
        return tableElement;
    }

    createRowElement() {
        const rowElement = document.createElement("tr");
        rowElement.classList.add("memory-game-row");
        return rowElement;
    }

    extractRandom(arr) {
        const index = Math.floor(Math.random() * arr.length);
        return arr.splice(index, 1)[0];
    }

    attachCellsData() {
        const emptyCells = this.cells.slice();
        let usableData = [];

        while (emptyCells.length) {
            if (!usableData || !usableData.length) {
                usableData = this.data.slice();
            }

            const firstCell = this.extractRandom(emptyCells);
            const secondCell = this.extractRandom(emptyCells);
            const data = this.extractRandom(usableData);
            firstCell.attachData(data);
            secondCell.attachData(data);
        }
    }

    detachCellsData() {
        for (const cell of this.cells) {
            cell.detachData();
            cell.setState(MemoryGameCellState.HIDDEN);
        }
    }

    populateElement() {
        this.cells = [];
        const tableElement = this.createTableElement();
        const onCellsClickFn = this.onCellClick.bind(this);

        for (let row = 0; row < this.rows; row++) {
            const rowElement = this.createRowElement();
            tableElement.appendChild(rowElement);

            for (let column = 0; column < this.cols; column++) {
                const cell = new MemoryGameCell(rowElement, {
                    type: this.type,
                    onClick: onCellsClickFn,
                });
                this.cells.push(cell);
            }
        }

        this.element.appendChild(tableElement)
    }

    setCellsState(cells, state) {
        for (const cell of cells) {
            cell.setState(state);
        }
    }

    setAllCellsState(state) {
        this.setCellsState(this.cells, state);
    }

    onCellClick(cell) {
        if (!this.interactive) {
            return;
        }

        if (this.matchedCells.includes(cell) || this.selectedCells.includes(cell)) {
            return;
        }

        if (this.showSelectedTimeout) {
            clearTimeout(this.showSelectedTimeout);
            this.lastShowSelectedTimeoutFn();
            this.showSelectedTimeout = null;
            this.lastShowSelectedTimeoutFn = null;
        }

        this.selectedCells.push(cell);

        cell.setState(MemoryGameCellState.SELECTED);

        if (this.selectedCells.length === 1) {
            return;
        }

        const isEqualCells = this.selectedCells[0].data === this.selectedCells[1].data;
        if (isEqualCells) {
            this.matchedCells = this.matchedCells.concat(this.selectedCells);
        }

        const lastSelectedCells = this.selectedCells.slice();
        const stateAfterTimeout = isEqualCells ? MemoryGameCellState.SOLVED : MemoryGameCellState.HIDDEN;
        this.lastShowSelectedTimeoutFn = () => {
            this.setCellsState(lastSelectedCells, stateAfterTimeout);
        };
        this.showSelectedTimeout = setTimeout(this.lastShowSelectedTimeoutFn, this.showDuration);

        this.selectedCells = [];
    }

    constructor(options) {
        this.element = options.element;
        this.data = options.data;
        this.type = options.type;
        this.rows = options.rows;
        this.cols = options.cols;
        this.showDuration = options.showDuration || 500;

        if ((this.rows * this.cols) % 2 === 1) {
            throw new Error("Cannot initialize memory game with an uneven number of cells");
        }

        this.populateElement();
    }

    reset() {
        if (this.showAllTimeout) {
            clearTimeout(this.showAllTimeout);
            this.showAllTimeout = null;
        }

        if (this.showSelectedTimeout) {
            clearTimeout(this.showSelectedTimeout);
            this.showSelectedTimeout = null;
        }

        this.setAllCellsState(MemoryGameCellState.HIDDEN);
        this.detachCellsData();
    }

    start() {
        this.reset();

        this.interactive = false;
        this.selectedCells = [];
        this.matchedCells = [];

        this.attachCellsData();
        this.setAllCellsState(MemoryGameCellState.VISIBLE);

        this.showAllTimeout = setTimeout(() => {
            this.interactive = true;
            this.showAllTimeout = null;
            this.setAllCellsState(MemoryGameCellState.HIDDEN);
        }, this.showDuration);
    }
}
