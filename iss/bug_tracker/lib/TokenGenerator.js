const jwt = require('jsonwebtoken');

class TokenGenerator {
    constructor(config) {
        this.config = config;
    }

    createToken(data, overrides) {
        return jwt.sign(data, this.config.secret, overrides);
    }

    createAccessToken(data) {
        return this.createToken(data, {
            expiresIn: config.accessTokenExpireTime,
        });
    }

    decodeToken(payload) {
        return jwt.verify(payload, this.config.secret);
    }
}

module.exports = TokenGenerator;
