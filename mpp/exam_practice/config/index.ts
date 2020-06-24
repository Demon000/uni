import Config from 'config';
import {CorsOptions} from 'cors';
import {ConnectionOptions} from 'typeorm';

import User from '../common/domain/User';
import {TokenGeneratorOptions} from '../server/lib/TokenGenerator';

export interface ConfigInterface {
    Server: {
        port: number,
        host: string,
    },
    Logger: {
        format: string,
    },
    Database: ConnectionOptions,
    TokenGenerator: TokenGeneratorOptions,
    Cors: CorsOptions,
    Users: [User],
}

const config: ConfigInterface = {
    Server: {
        port: Config.get('Server.port'),
        host: Config.get('Server.host'),
    },
    Logger: {
        format: Config.get('Logger.format'),
    },
    Database: Config.get('Database'),
    TokenGenerator: Config.get('TokenGenerator'),
    Cors: Config.get('Cors'),
    Users: Config.get('Users'),
};

export default config;
