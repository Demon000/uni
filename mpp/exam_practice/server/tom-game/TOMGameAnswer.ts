import Answer from '../base-game/Answer';

export default class TOMGameAnswer extends Answer {
    country: string;
    city: string;
    sea: string;

    constructor(country: string, city: string, sea: string) {
        super();

        this.country = country;
        this.city = city;
        this.sea = sea;
    }
}
