<?php


namespace App\TicTacToe;


use Exception;
use Symfony\Component\HttpFoundation\JsonResponse;

class GameError extends Exception {
    private string $error_code;
    private int $status;

    public function __construct($message, $error_code, $status) {
        parent::__construct($message);
        $this->error_code = $error_code;
        $this->status = $status;
    }

    public static function NotStarted() {
        return new GameError('Game not started', 'not-started', 400);
    }

    public static function NotRunning() {
        return new GameError('Game not running', 'not-running', 400);
    }

    public static function CellNotEmptyError() {
        return new GameError('Game cell not empty', 'cell-not-empty', 400);
    }

    public static function CellInvalidError() {
        return new GameError('Game cell is invalid', 'cell-invalid', 400);
    }

    public static function MoveMissingError() {
        return new GameError('Game move is missing', 'move-missing', 400);
    }

    public function toResponse() {
        $response = new JsonResponse(array(
                'error' => true,
                'code' => $this->error_code,
                'message' => $this->getMessage(),
        ));
        $response->setStatusCode($this->status);
        return $response;
    }
}
