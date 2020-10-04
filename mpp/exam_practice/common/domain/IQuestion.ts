import IConfiguration from './IConfiguration';

export default interface IQuestion extends IConfiguration {
    round: number;
    id: number;
}
