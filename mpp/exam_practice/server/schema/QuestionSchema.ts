import {EntitySchema} from 'typeorm';
import Question from '../../common/domain/Question';

export default new EntitySchema<Question>({
    name: 'question',
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
        configuration: {
            type: 'simple-json',
            nullable: false,
        },
    },
});
