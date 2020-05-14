<?php


namespace App\FileExplorer;


use Exception;
use Symfony\Component\HttpFoundation\JsonResponse;

class FileError extends Exception {
    private string $error_code;
    private int $status;

    public function __construct($message, $error_code, $status) {
        parent::__construct($message);
        $this->error_code = $error_code;
        $this->status = $status;
    }

    public static function NotFound() {
        return new FileError('File not found', 'file-not-found', 400);
    }

    public static function OutsideRoot() {
        return new FileError('File is outside root directory', 'outside-root', 400);
    }

    public function toResponse() {
        $response = new JsonResponse([
                'error' => true,
                'code' => $this->error_code,
                'message' => $this->getMessage(),
        ]);
        $response->setStatusCode($this->status);
        return $response;
    }
}
