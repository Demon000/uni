class BugStatuses {
    static OPEN = 'OPEN';
    static CLOSED = 'CLOSED';
    static ALL = 'ALL';

    static getValues() {
        return [
            this.OPEN,
            this.CLOSED,
        ];
    }

    static fromString(status) {
        switch (status.toUpperCase()) {
            case 'OPEN':
                return this.OPEN;
            case 'CLOSED':
                return this.CLOSED;
            default:
                return this.ALL;
        }
    }
}

module.exports = BugStatuses;
