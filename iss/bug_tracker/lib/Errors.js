const errors = {
    400: {
        HelloError: {
            code: 'hello-error',
            message: 'Hello error.'
        },
    },
};

function generate(name, status, code, message) {
    class CustomError extends Error {
        constructor() {
            super(message);
            this.name = name;
            this.code = code;
            this.status = status;
        }
    }

    return CustomError;
}

const constructors = {};
for (const status in errors) {
    const group = errors[status];
    for (let name in group) {
        if (!group.hasOwnProperty(name)) {
            continue;
        }

        const { code, message } = group[name];
        constructors[name] = generate(name, status, code, message);
    }
}

module.exports = constructors;
