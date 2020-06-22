import Config from 'config';
import UserInterface from '../model/UserInterface';
import {CorsOptions} from 'cors';

export interface ConfigInterface {
    Server: {
        port: number,
        host: string,
    },
    Logger: {
        format: string,
    },
    Cors: CorsOptions,
    Users: [UserInterface],
}

const config: ConfigInterface = {
    Server: {
        port: Config.get('Server.port'),
        host: Config.get('Server.host'),
    },
    Logger: {
        format: Config.get('Logger.format'),
    },
    Cors: Config.get('Cors'),
    Users: Config.get('Users'),
};

export default config;
