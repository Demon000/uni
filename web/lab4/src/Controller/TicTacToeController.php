<?php

namespace App\Controller;

use App\TicTacToe\GameCellState;
use App\TicTacToe\GameError;
use App\TicTacToe\GameState;
use App\TicTacToe\GameTable;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\JsonResponse;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\Session\SessionInterface;
use Symfony\Component\Routing\Annotation\Route;

/**
 * @Route("/api/tic_tac_toe", name="tic_tac_toe_")
 */
class TicTacToeController extends AbstractController {
    const SESSION_TABLE = "tic_tac_toe_table";
    private SessionInterface $session;

    public function __construct(SessionInterface $session) {
        $this->session = $session;
    }

    public function getGameTable() {
        return $this->session->get(self::SESSION_TABLE);
    }

    public function setGameTable($table) {
        $this->session->set(self::SESSION_TABLE, $table);
    }

    public function getGameState() {
        $table = $this->session->get(self::SESSION_TABLE);
        return GameTable::getState($table);
    }

    public function getGameResponse() {
        return new JsonResponse(array(
                'table' => $this->getGameTable(),
                'state' => $this->getGameState(),
        ));
    }

    public function isGameRunning() {
        $state = $this->getGameState();
        return GameState::isRunning($state);
    }

    public function isGameStarted() {
        $state = $this->getGameState();
        return GameState::isStarted($state);
    }

    /**
     * @Route("/state", methods={"GET"}, name="state")
     * @return JsonResponse
     */
    public function state() {
        if (!$this->isGameStarted()) {
            return GameError::NotStarted()->toResponse();
        }

        return $this->getGameResponse();
    }

    /**
     * @Route("/start", methods={"POST"}, name="start")
     * @return JsonResponse
     */
    public function start() {
        $table = GameTable::createTable();

        $player = GameTable::getRandomPlayer();
        if ($player == GameCellState::COMPUTER) {
            try {
                GameTable::makeBestMove($table, $player);
            } catch (GameError $e) {
                return $e->toResponse();
            }
        }

        $this->setGameTable($table);

        return $this->getGameResponse();
    }

    /**
     * @param $user_move
     * @throws GameError
     */
    public function playRound($user_move) {
        $table = $this->getGameTable();
        GameTable::makeMove($table, $user_move, GameCellState::USER);
        GameTable::makeBestMove($table, GameCellState::COMPUTER);
        $this->setGameTable($table);
    }

    const REQUEST_BODY_MOVE_KEY = 'move';
    /**
     * @Route("/play", methods={"POST"}, name="play")
     * @param Request $request
     * @return JsonResponse
     */
    public function play(Request $request) {
        if (!$this->isGameStarted()) {
            return GameError::NotStarted()->toResponse();
        }

        if (!$this->isGameRunning()) {
            return GameError::NotRunning()->toResponse();
        }

        $body = json_decode($request->getContent(), true);
        if (!array_key_exists(self::REQUEST_BODY_MOVE_KEY, $body)) {
            return GameError::MoveMissingError()->toResponse();
        }

        $move = $body[self::REQUEST_BODY_MOVE_KEY];
        if (count($move) != 2) {
            return GameError::MoveMissingError()->toResponse();
        }

        try {
            $this->playRound($move);
        } catch (GameError $e) {
            return $e->toResponse();
        }

        return $this->getGameResponse();
    }
}
