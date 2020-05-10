class BugStatuses {
    static OPEN = 'OPEN';
    static SOLVED = 'SOLVED';
    static ALL = 'ALL';

    static getValues() {
        return [
            this.OPEN,
            this.SOLVED,
        ];
    }

    static fromString(status) {
        switch (status.toUpperCase()) {
            case 'OPEN':
                return this.OPEN;
            case 'SOLVED':
                return this.SOLVED;
            default:
                return this.ALL;
        }
    }
}

module.exports = BugStatuses;
