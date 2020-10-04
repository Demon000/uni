import IQuestion from './IQuestion';

export default class Question implements IQuestion {
    round: number;
    id: number;

    configuration: string[];

    constructor(options?: Partial<IQuestion>) {
        this.round = options?.round || 0;
        this.id = options?.id || 0;

        this.configuration = options?.configuration || [];
    }

    toSafe(): IQuestion {
        return {
            round: this.round,
            id: this.id,
            configuration: this.configuration,
        };
    }
}
