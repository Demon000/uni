import jwt, {Secret, SignOptions} from 'jsonwebtoken';

export interface TokenGeneratorOptions {
    secret: Secret;
    accessTokenExpireTime: string | number;
}

export default class TokenGenerator {
    private config: TokenGeneratorOptions;

    constructor(config: TokenGeneratorOptions) {
        this.config = config;
    }

    createToken(data: object, overrides: SignOptions) {
        return jwt.sign(data, this.config.secret, overrides);
    }

    createAccessToken(data: object) {
        return this.createToken(data, {
            expiresIn: this.config.accessTokenExpireTime,
        });
    }

    decodeToken(payload: string) {
        return jwt.verify(payload, this.config.secret);
    }
}