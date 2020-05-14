<?php

namespace App\Controller;

use App\TicTacToe\GameCellState;
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

    public function getGameStateResponse($started_check=false, $running_check=false) {
        $table = $this->getGameTable();
        $state = $this->getGameState();

        if ($running_check == true && GameState::isRunning($state)) {
            return null;
        }

        if ($started_check == true && GameState::isStarted($state)) {
            return null;
        }

        return new JsonResponse(array(
                'state' => $state,
                'table' => $table,
        ));
    }

    /**
     * @Route("/state", methods={"GET"}, name="state")
     * @return JsonResponse
     */
    public function state() {
        return $this->getGameStateResponse();
    }

    /**
     * @Route("/start", methods={"POST"}, name="start")
     * @return JsonResponse
     */
    public function start() {
        $table = GameTable::createTable();

        $player = GameTable::getRandomPlayer();
        if ($player == GameCellState::COMPUTER) {
            GameTable::makeBestMove($table, $player);
        }

        $this->setGameTable($table);

        return $this->getGameStateResponse();
    }

    public function playRound($user_move) {
        $table = $this->getGameTable();
        GameTable::makeMove($table, $user_move, GameCellState::USER);
        GameTable::makeBestMove($table, GameCellState::COMPUTER);
    }

    const REQUEST_BODY_MOVE_KEY = 'move';
    /**
     * @Route("/play", methods={"POST"}, name="play")
     * @param Request $request
     * @return JsonResponse
     */
    public function play(Request $request) {
        $response = $this->getGameStateResponse(true, true);
        if ($response != null) {
            return $response;
        }

        $body = json_decode($request->getContent(), true);
        if (!array_key_exists(self::REQUEST_BODY_MOVE_KEY, $body)) {
            if (array_count_values($body) == 2) {
                $move = $body[self::REQUEST_BODY_MOVE_KEY];
                $this->playRound($move);
            }
        }

        return $this->$this->getGameStateResponse();
    }
}
