import {EntitySchema} from 'typeorm';
import Question from '../../common/domain/Question';

export default new EntitySchema<Question>({
    name: 'tom_question',
    target: Question,
    columns: {
        id: {
            type: 'integer',
            primary: true,
            generated: 'increment',
            nullable: false,
        },
        round: {
            type: 'integer',
            nullable: false,
        },
        letter: {
            type: 'nvarchar',
            nullable: false,
            length: 255,
        },
    },
    relations: {
        player: {
            type: 'one-to-one',
            target: 'user',
            eager: true,
        },
    },
});
