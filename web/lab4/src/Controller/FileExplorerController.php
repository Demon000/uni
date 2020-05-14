<?php

namespace App\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\Routing\Annotation\Route;

/**
 * @Route("/api/file_explorer", name="file_explorer_")
 */
class FileExplorerController extends AbstractController
{
    /**
     * @Route("/{filePath}", name="list")
     * @param string $filePath
     */
    public function list(string $filePath)
    {
    }
}
