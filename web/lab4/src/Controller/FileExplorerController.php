<?php

namespace App\Controller;

use App\FileExplorer\File;
use App\FileExplorer\FileError;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\JsonResponse;
use Symfony\Component\Routing\Annotation\Route;

/**
 * @Route("/api/file_explorer", name="file_explorer_")
 */
class FileExplorerController extends AbstractController {
    const FILE_EXPLORER_ROOT_KEY = 'FILE_EXPLORER_ROOT';

    /**
     * @Route("/{relative_file_path}", name="list", defaults={"relative_file_path"="/"},
     *     requirements={"relative_file_path"=".+"})
     * @param string $relative_file_path
     * @return JsonResponse
     */
    public function list(string $relative_file_path) {
        try {
            $file_explorer_root = $this->getFileExplorerRootPath();
            $file = new File($file_explorer_root, $relative_file_path);
        } catch (FileError $e) {
            return $e->toResponse();
        }

        $file->populateFiles();

        return $this->json($file);
    }

    /**
     * @return string
     * @throws FileError
     */
    public function getFileExplorerRootPath() {
        if (!array_key_exists(self::FILE_EXPLORER_ROOT_KEY, $_ENV)) {
            throw FileError::NotFound();
        }
        return $_ENV[self::FILE_EXPLORER_ROOT_KEY];
    }
}
