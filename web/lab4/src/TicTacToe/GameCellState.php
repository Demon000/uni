<?php


namespace App\TicTacToe;


class GameCellState
{
    const EMPTY = 'empty';
    const USER = 'user';
    const COMPUTER = 'computer';

    public static function getGameState(string $value)
    {
        switch ($value)
        {
            case self::USER:
                return GameState::WIN_USER;
            case self::COMPUTER:
                return GameState::WIN_COMPUTER;
            default:
                return GameState::UNKNOWN;
        }
    }
}