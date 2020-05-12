<?php

namespace App\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\Session\SessionInterface;
use Symfony\Component\Routing\Annotation\Route;

/**
 * @Route("/api/tic_tac_toe", name="tic_tac_toe_")
 */
class TicTacToeController extends AbstractController
{
    /**
     * @Route("/state", methods={"GET"} name="state")
     * @param SessionInterface $session
     */
    public function state(SessionInterface $session)
    {

    }

    /**
     * @Route("/start", methods={"POST"} name="start")
     */
    public function start()
    {

    }

    /**
     * @Route("/play", methods={"POST"} name="play")
     */
    public function play()
    {
    }
}
