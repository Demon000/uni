<?php

namespace App\Entity;

use App\Repository\PersonRepository;
use Doctrine\ORM\Mapping as ORM;
use JsonSerializable;

/**
 * @ORM\Entity(repositoryClass=PersonRepository::class)
 */
class Person implements JsonSerializable {
    /**
     * @ORM\Id()
     * @ORM\GeneratedValue()
     * @ORM\Column(type="integer")
     */
    private $id;

    /**
     * @ORM\Column(type="string", length=255)
     */
    private $first_name;

    /**
     * @ORM\Column(type="string", length=255)
     */
    private $last_name;

    /**
     * @ORM\Column(type="string", length=255)
     */
    private $phone;

    /**
     * @ORM\Column(type="string", length=255)
     */
    private $email;

    public function jsonSerialize() {
        return [
                'id' => $this->getId(),
                'first_name' => $this->getFirstName(),
                'last_name' => $this->getLastName(),
                'phone' => $this->getPhone(),
                'email' => $this->getEmail(),
        ];
    }

    public function getId(): ?int {
        return $this->id;
    }

    public function getFirstName(): ?string {
        return $this->first_name;
    }

    public function setFirstName(string $first_name): self {
        $this->first_name = $first_name;

        return $this;
    }

    public function getLastName(): ?string {
        return $this->last_name;
    }

    public function setLastName(string $last_name): self {
        $this->last_name = $last_name;

        return $this;
    }

    public function getPhone(): ?string {
        return $this->phone;
    }

    public function setPhone(string $phone): self {
        $this->phone = $phone;

        return $this;
    }

    public function getEmail(): ?string {
        return $this->email;
    }

    public function setEmail(string $email): self {
        $this->email = $email;

        return $this;
    }
}
