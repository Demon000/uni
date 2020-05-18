<?php

namespace App\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\Routing\Annotation\Route;

class WebController extends AbstractController
{
    /**
     * @Route("/ajax_1", name="ajax_1")
     */
    public function ajax_1()
    {
        return $this->render('ajax_1.html.twig', [
            'controller_name' => 'WebController',
        ]);
    }

    /**
     * @Route("/ajax_2", name="ajax_2")
     */
    public function ajax_2()
    {
        return $this->render('ajax_2.html.twig', [
                'controller_name' => 'WebController',
        ]);
    }

    /**
     * @Route("/ajax_3", name="ajax_3")
     */
    public function ajax_3()
    {
        return $this->render('ajax_3.html.twig', [
                'controller_name' => 'WebController',
        ]);
    }

    /**
     * @Route("/ajax_4", name="ajax_4")
     */
    public function ajax_4()
    {
        return $this->render('ajax_4.html.twig', [
                'controller_name' => 'WebController',
        ]);
    }

    /**
     * @Route("/ajax_5", name="ajax_5")
     */
    public function ajax_5()
    {
        return $this->render('ajax_5.html.twig', [
                'controller_name' => 'WebController',
        ]);
    }

    /**
     * @Route("/ajax_6", name="ajax_5")
     */
    public function ajax_6()
    {
        return $this->render('ajax_6.html.twig', [
                'controller_name' => 'WebController',
        ]);
    }
}
