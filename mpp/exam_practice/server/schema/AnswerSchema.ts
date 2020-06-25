import {EntitySchema, EntitySchemaRelationOptions} from 'typeorm';
import Answer from '../../common/domain/Answer';

export default new EntitySchema<Answer>({
    name: 'tom_answer',
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
        points: {
            type: 'integer',
            nullable: false,
        },
        country: {
            type: 'nvarchar',
            nullable: false,
            length: 255,
        },
        city: {
            type: 'nvarchar',
            nullable: false,
            length: 255,
        },
        mountain: {
            type: 'nvarchar',
            nullable: false,
            length: 255,
        },
    },
    relations: {
        question: {
            type: 'one-to-one',
            target: 'question',
            eager: true,
        } as EntitySchemaRelationOptions,
        player: {
            type: 'one-to-one',
            target: 'user',
            eager: true,
        } as EntitySchemaRelationOptions,
    },
});
