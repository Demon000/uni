import Answer from '../base-game/Answer';

export interface ITOMAnswer {
    country: string;
    city: string;
    sea: string;
}

export default class TOMAnswer extends Answer implements ITOMAnswer {
    country: string;
    city: string;
    sea: string;

    constructor(options: ITOMAnswer) {
        super();

        this.country = options.country;
        this.city = options.city;
        this.sea = options.sea;
    }
}
