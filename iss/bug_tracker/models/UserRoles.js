class UserRoles {
    static TESTER = "TESTER";
    static PROGRAMMER = "PROGRAMMER";
    static ADMIN = "ADMIN";

    static getValues() {
        return [
            this.TESTER,
            this.PROGRAMMER,
            this.ADMIN,
        ];
    }
}

module.exports = UserRoles;
