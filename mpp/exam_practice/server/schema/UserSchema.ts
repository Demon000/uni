import {EntitySchema} from 'typeorm';
import User from '../../common/domain/User';

export default new EntitySchema<User>({
    name: 'user',
    target: User,
    columns: {
        id: {
            type: 'integer',
            primary: true,
            generated: 'increment',
            nullable: false,
        },
        username: {
            type: 'nvarchar',
            nullable: false,
            unique: true,
            length: 255,
        },
        password: {
            type: 'nvarchar',
            nullable: false,
            length: 255,
        },
    }
});
