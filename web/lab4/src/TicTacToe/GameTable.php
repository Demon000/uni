<?php


namespace App\TicTacToe;

class GameTable {
    public static function createTable() {
        return array(
                self::createRow(),
                self::createRow(),
                self::createRow(),
        );
    }

    public static function createRow() {
        return array(GameCellState::EMPTY, GameCellState::EMPTY, GameCellState::EMPTY);
    }

    public static function getState($table) {
        if ($table == null) {
            return GameState::NOT_STARTED;
        }

        $winningCell = self::getWinningCell($table);
        $gameState = GameCellState::getGameState($winningCell);
        if ($gameState != GameState::UNKNOWN) {
            return $gameState;
        }

        $anyEmpty = false;
        for ($i = 0; $i < 3; $i++) {
            for ($j = 0; $j < 3; $j++) {
                if ($table[$i][$j] == GameCellState::EMPTY) {
                    $anyEmpty = true;
                }
            }
        }

        if ($anyEmpty) {
            return GameState::RUNNING;
        } else {
            return GameState::DRAW;
        }
    }

    public static function getWinningCell($table) {
        for ($i = 0; $i < 3; $i++) {
            if ($table[$i][0] == $table[$i][1] &&
                    $table[$i][1] == $table[$i][2]) {
                return $table[$i][0];
            } else if ($table[0][$i] == $table[1][$i] &&
                    $table[1][$i] == $table[2][$i]) {
                return $table[0][$i];
            }
        }

        if (($table[0][0] == $table[1][1] && $table[1][1] == $table[2][2]) ||
                ($table[0][2] == $table[1][1] && $table[1][1] == $table[2][0])) {
            return $table[1][1];
        }

        return GameCellState::EMPTY;
    }

    public static function getAvailableMoves($table) {
        $moves = array();

        for ($i = 0; $i < 3; $i++) {
            for ($j = 0; $j < 3; $j++) {
                if ($table[$i][$j] == GameCellState::EMPTY) {
                    array_push($moves, array($i, $j));
                }
            }
        }

        return $moves;
    }

    public static function copyTable($table) {
        $table_copy = array();
        for ($i = 0; $i < 3; $i++) {
            $row = array();
            for ($j = 0; $j < 3; $j++) {
                array_push($row, $table[$i][$j]);
            }
            array_push($table_copy, $row);
        }
        return $table_copy;
    }

    /**
     * @param $table
     * @param $move
     * @param $player
     * @throws GameError
     */
    public static function makeMove(&$table, $move, $player) {
        $i = $move[0];
        $j = $move[1];

        if ($i < 0 || $i > 2 || $j < 0 || $j > 2) {
            throw GameError::CellInvalidError();
        }

        if ($table[$i][$j] != GameCellState::EMPTY) {
            throw GameError::CellNotEmptyError();
        }

        $table[$i][$j] = $player;
    }

    /**
     * @param $table
     * @param $player
     * @return int
     * @throws GameError
     */
    public static function makeBestMove(&$table, $player) {
        $opponent = GameCellState::getOpponent($player);
        $winner = self::getWinningCell($table);
        if ($winner == $player) {
            return 1;
        } elseif ($winner == $opponent) {
            return -1;
        }

        $final_move = null;
        $final_score = -2;
        $moves = self::getAvailableMoves($table);

        foreach ($moves as $move) {
            $test_table = self::copyTable($table);
            self::makeMove($test_table, $move, $player);

            $test_score = -self::makeBestMove($test_table, $opponent);
            if ($test_score > $final_score) {
                $final_score = $test_score;
                $final_move = $move;
            }

            if ($final_score == 1) {
                break;
            }
        }

        if ($final_move != null) {
            self::makeMove($table, $final_move, $player);
        }

        return $final_score;
    }

    public static function getRandomPlayer() {
        $random = rand() / getrandmax();
        if ($random < 0.5) {
            return GameCellState::COMPUTER;
        }

        return GameCellState::USER;
    }
}
