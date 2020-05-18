<?php

namespace App\Controller;

use App\TicTacToe\GameCellState;
use App\TicTacToe\GameError;
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
    const REQUEST_BODY_MOVE_KEY = 'move';
    private SessionInterface $session;

    public function __construct(SessionInterface $session) {
        $this->session = $session;
    }

    /**
     * @return GameTable
     * @throws GameError
     */
    public function getGameTable() {
        $inner_table = $this->session->get(self::SESSION_TABLE);
        if ($inner_table == null) {
            throw GameError::NotStarted();
        }
        return new GameTable($inner_table);
    }

    public function getGameResponse($table) {
        return $this->json([
                'table' => $table->getInnerTable(),
                'state' => $table->getState(),
        ]);
    }

    /**
     * @Route("/state", methods={"GET"}, name="state")
     * @return JsonResponse
     */
    public function state() {
        try {
            $table = $this->getGameTable();
        } catch (GameError $e) {
            return $e->toResponse();
        }

        return $this->getGameResponse($table);
    }

    public function setGameTable($table) {
        $inner_table = $table->getInnerTable();
        $this->session->set(self::SESSION_TABLE, $inner_table);
    }

    /**
     * @Route("/start", methods={"POST"}, name="start")
     * @return JsonResponse
     */
    public function start() {
        $table = new GameTable();

        $player = GameCellState::getRandomPlayer();
        if ($player == GameCellState::COMPUTER) {
            try {
                $table->makeBestMove($player);
            } catch (GameError $e) {
                return $e->toResponse();
            }
        }

        $this->setGameTable($table);

        return $this->getGameResponse($table);
    }

    /**
     * @Route("/play", methods={"POST"}, name="play")
     * @param Request $request
     * @return JsonResponse
     */
    public function play(Request $request) {
        try {
            $table = $this->getGameTable();
        } catch (GameError $e) {
            return $e->toResponse();
        }

        if (!$table->isRunning()) {
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
            $table->makeMove($move, GameCellState::USER);
            $table->makeBestMove(GameCellState::COMPUTER);
        } catch (GameError $e) {
            return $e->toResponse();
        }

        $this->setGameTable($table);

        return $this->getGameResponse($table);
    }
}
