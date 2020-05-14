<?php


namespace App\TicTacToe;


class GameCellState {
    const EMPTY = 'empty';
    const USER = 'user';
    const COMPUTER = 'computer';

    public static function getGameState(string $value): string {
        switch ($value) {
            case self::USER:
                return GameState::WIN_USER;
            case self::COMPUTER:
                return GameState::WIN_COMPUTER;
            default:
                return GameState::UNKNOWN;
        }
    }

    public static function getOpponent(string $value): string {
        switch ($value) {
            case self::USER:
                return self::COMPUTER;
            case self::COMPUTER:
                return self::USER;
            default:
                return self::EMPTY;
        }
    }

    public static function getRandomPlayer() {
        $random = rand() / getrandmax();
        if ($random < 0.5) {
            return self::COMPUTER;
        }

        return self::USER;
    }
}
