import ISafeUser from './ISafeUser';

export default interface IQuestion {
    round: number;
    id: number;
    player: ISafeUser | undefined;

    // TODO
    letter: string;
}
