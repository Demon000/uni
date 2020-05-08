module.exports = {
    "env": {
        "es6": true,
        "node": true
    },
    "extends": "eslint:recommended",
    "parser": "babel-eslint",
    "parserOptions": {
        "ecmaVersion": 2018,
        "sourceType": "module"
    },
    "ignorePatterns": [
        "web/dist/*.js",
        "node_modules/"
    ],
    "rules": {
        "quotes": [
            "error",
            "single"
        ],
        "semi": [
            "error",
            "always"
        ],
        "eol-last": [
            "error",
            "always"
        ],
        "keyword-spacing": [
            "error", {
                "before": true,
                "after": true
            }
        ],
        "no-trailing-spaces": [
            "error"
        ],
        "max-len": [
            "error", {
                "code": 100,
                "tabWidth": 4
            }
        ],
        "require-await": "error",
        "curly": [
            "error",
            "all"
        ],
        "dot-location": [
            "error",
            "property"
        ],
        "dot-notation": "error",
        "array-callback-return": "error",
        "class-methods-use-this": "error",
    }
};
