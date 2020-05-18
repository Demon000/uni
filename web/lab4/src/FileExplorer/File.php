<?php


namespace App\FileExplorer;


use JsonSerializable;

class File implements JsonSerializable {
    private string $type;
    private string $mime;
    private string $root_path;
    private string $absolute_path;
    private string $relative_path;
    private string $name;
    private array $files = [];

    /**
     * File constructor.
     * @param string $root_path
     * @param string $relative_file_path
     * @throws FileError
     */
    public function __construct(string $root_path, string $relative_file_path) {
        $real_root = realpath($root_path);
        $file_path = realpath($root_path . $relative_file_path);

        if (!$file_path) {
            throw FileError::NotFound();
        }

        if (strpos($real_root, $file_path) != 0) {
            throw FileError::OutsideRoot();
        }

        if (is_dir($file_path)) {
            $this->type = FileType::DIRECTORY;
            $file_path = self::addTrailingSlash($file_path);
            $relative_file_path = self::addTrailingSlash($relative_file_path);
        } else {
            $this->type = FileType::FILE;
        }

        $this->mime = mime_content_type($file_path);

        $this->root_path = $root_path;
        $this->absolute_path = $file_path;
        $this->relative_path = $relative_file_path;
        $this->name = pathinfo($file_path, PATHINFO_BASENAME);
    }

    public static function addTrailingSlash($path) {
        return rtrim($path, DIRECTORY_SEPARATOR) . DIRECTORY_SEPARATOR;
    }

    public function getPath() {
        return $this->relative_path;
    }

    public function populateFiles() {
        if ($this->type != FileType::DIRECTORY) {
            return;
        }

        $partial_paths = array_diff(scandir($this->absolute_path), ['..', '.']);
        $this->files = [];

        foreach ($partial_paths as $partial_path) {
            try {
                $relative_path = $this->relative_path . $partial_path;
                array_push($this->files, new File($this->root_path, $relative_path));
            } catch (FileError $e) {
            }
        }
    }

    public function jsonSerialize() {
        $data = [
                'path' => $this->relative_path,
                'name' => $this->name,
                'type' => $this->type,
                'mime' => $this->mime,
        ];

        if ($this->files) {
            $data['files'] = $this->files;
        }

        return $data;
    }
}
