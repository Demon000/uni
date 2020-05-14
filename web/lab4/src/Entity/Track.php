<?php

namespace App\Entity;

use App\Repository\TrackRepository;
use Doctrine\ORM\Mapping as ORM;

/**
 * @ORM\Entity(repositoryClass=TrackRepository::class)
 */
class Track {
    /**
     * @ORM\Id()
     * @ORM\GeneratedValue()
     * @ORM\Column(type="integer")
     */
    private $id;

    /**
     * @ORM\ManyToOne(targetEntity=City::class)
     * @ORM\JoinColumn(nullable=false)
     */
    private $fromCity;

    /**
     * @ORM\ManyToOne(targetEntity=City::class)
     * @ORM\JoinColumn(nullable=false)
     */
    private $toCity;

    public function getId(): ?int {
        return $this->id;
    }

    public function getFromCity(): ?City {
        return $this->fromCity;
    }

    public function setFromCity(?City $fromCity): self {
        $this->fromCity = $fromCity;

        return $this;
    }

    public function getToCity(): ?City {
        return $this->toCity;
    }

    public function setToCity(?City $toCity): self {
        $this->toCity = $toCity;

        return $this;
    }
}
