<?php


namespace App\TicTacToe;

class GameTable {
    private array $table;

    public function __construct($table = null) {
        if ($table == null) {
            $table = $this->createInnerTable();
        }

        $this->table = $table;
    }

    public static function createInnerTable() {
        return [
                self::createRow(),
                self::createRow(),
                self::createRow(),
        ];
    }

    public static function createRow() {
        return array(GameCellState::EMPTY, GameCellState::EMPTY, GameCellState::EMPTY);
    }

    public function getInnerTable() {
        return $this->table;
    }

    public function isRunning() {
        return $this->getState() == GameState::RUNNING;
    }

    public function getState() {
        if ($this->table == null) {
            return GameState::NOT_STARTED;
        }

        $winningCell = $this->getWinningCell($this->table);
        $gameState = GameCellState::getGameState($winningCell);
        if ($gameState != GameState::UNKNOWN) {
            return $gameState;
        }

        $anyEmpty = false;
        for ($i = 0; $i < 3; $i++) {
            for ($j = 0; $j < 3; $j++) {
                if ($this->table[$i][$j] == GameCellState::EMPTY) {
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

    private static function getWinningCell($table) {
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

    /**
     * @param $move
     * @param $player
     * @throws GameError
     */
    public function makeMove($move, $player) {
        self::makeMoveInner($this->table, $move, $player);
    }

    /**
     * @param $table
     * @param $move
     * @param $player
     * @throws GameError
     */
    private static function makeMoveInner(&$table, $move, $player) {
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
     * @param $player
     * @return int
     * @throws GameError
     */
    public function makeBestMove($player) {
        return self::makeBestMoveInner($this->table, $player);
    }

    /**
     * @param $table
     * @param $player
     * @return int
     * @throws GameError
     */
    private static function makeBestMoveInner(&$table, $player) {
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
            self::makeMoveInner($test_table, $move, $player);

            $test_score = -self::makeBestMoveInner($test_table, $opponent);
            if ($test_score > $final_score) {
                $final_score = $test_score;
                $final_move = $move;
            }

            if ($final_score == 1) {
                break;
            }
        }

        if ($final_move == null) {
            return 0;
        }

        self::makeMoveInner($table, $final_move, $player);
        return $final_score;
    }

    private static function getAvailableMoves($table) {
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

    private static function copyTable($table) {
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
}
