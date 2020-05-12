<?php


namespace App\TicTacToe;

use App\Entity\Person;

class GameTable
{
    private $table;

    public function __construct()
    {

    }

    public function createTable()
    {
        $this->table = array(
            $this->createRow(),
            $this->createRow(),
            $this->createRow(),
        );
    }

    public function createRow()
    {
        return array(GameCellState::EMPTY, GameCellState::EMPTY, GameCellState::EMPTY);
    }

    public function getTable()
    {
        return $this->copyTable();
    }

    public function getWinningCell($table)
    {
        for ($i = 0; $i < 3; $i++)
        {
            if ($table[$i][0] == $table[$i][1] &&
                $table[$i][1] == $table[$i][2])
            {
                return $table[$i][0];
            }
            else if ($table[0][$i] == $table[1][$i] &&
                $table[1][$i] == $table[2][$i])
            {
                return $table[0][$i];
            }
        }

        if (($table[0][0] == $table[1][1] && $table[1][1] == $table[2][2]) ||
            ($table[0][2] == $table[1][1] && $table[1][1] == $table[2][0]))
        {
            return $table[1][1];
        }
    }

    public function getState()
    {
        $winningCell = $this->getWinningCell($this->table);
        $gameState = GameCellState::getGameState($winningCell);
        if ($gameState != GameState::UNKNOWN)
        {
            return $gameState;
        }

        $anyEmpty = false;
        for ($i = 0; $i < 3; $i++)
        {
            for ($j = 0; $j < 3; $j++)
            {
                if ($this->table[$i][$j] == GameCellState::EMPTY)
                {
                    $anyEmpty = true;
                }
            }
        }

        if ($anyEmpty)
        {
            return GameState::RUNNING;
        }
        else
        {
            return GameState::DRAW;
        }
    }

    public function copyTable()
    {
        $table = array();
        for ($i = 0; $i < 3; $i++)
        {
            array_push($table, array());
            for ($j = 0; $j < 3; $j++)
            {
                array_push(end($table), $this->table[$i][$j]);
            }
        }
        return $table;
    }

    public function moveComputer()
    {

    }
}