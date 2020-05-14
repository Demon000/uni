<?php

namespace App\Entity;

use App\Repository\CityRepository;
use Doctrine\ORM\Mapping as ORM;
use JsonSerializable;

/**
 * @ORM\Entity(repositoryClass=CityRepository::class)
 */
class City implements JsonSerializable {
    /**
     * @ORM\Id()
     * @ORM\GeneratedValue()
     * @ORM\Column(type="integer")
     */
    private $id;

    /**
     * @ORM\Column(type="string", length=255)
     */
    private $name;

    private array $connections = [];

    public function jsonSerialize() {
        $data = [
                'id' => $this->id,
                'name' => $this->name,
        ];

        if ($this->connections) {
            $data['connections'] = $this->connections;
        }

        return $data;
    }

    public function getId(): ?int {
        return $this->id;
    }

    public function getName(): ?string {
        return $this->name;
    }

    public function setName(string $name): self {
        $this->name = $name;
        return $this;
    }

    public function setConnections(array $connections): self {
        $this->connections = $connections;
        return $this;
    }
}
