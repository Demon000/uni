import ISafeUser from './ISafeUser';

export default interface IUser extends ISafeUser {
    password: string;
}