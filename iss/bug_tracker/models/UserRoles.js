class UserRoles {
    static TESTER = 'TESTER';
    static PROGRAMMER = 'PROGRAMMER';
    static ADMIN = 'ADMIN';

    static getValues() {
        return [
            this.TESTER,
            this.PROGRAMMER,
            this.ADMIN,
        ];
    }

    static isExactRole(role, targetRole) {
        return role === targetRole;
    }

    static isCompatibleRole(role, targetRole) {
        if (role === targetRole || (targetRole == null && role)) {
            return true;
        }

        switch (role) {
            case this.PROGRAMMER:
                if ([this.TESTER].includes(targetRole)) {
                    return true;
                }
                break;
            case this.ADMIN:
                if ([this.PROGRAMMER, this.TESTER].includes(targetRole)) {
                    return true;
                }
                break
        }

        return false;
    }
}

module.exports = UserRoles;
