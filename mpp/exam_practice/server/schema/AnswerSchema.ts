import {EntitySchema} from 'typeorm';
import Answer from '../../common/domain/Answer';

export default new EntitySchema<Answer>({
    name: 'answer',
    target: Answer,
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
        roll: {
            type: 'integer',
            nullable: false,
        },
    },
    relations: {
        question: {
            type: 'one-to-one',
            target: 'question',
            eager: true,
        },
        player: {
            type: 'one-to-one',
            target: 'user',
            eager: true,
        },
    },
});
