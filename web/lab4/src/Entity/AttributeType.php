<?php

namespace App\Entity;

use App\Repository\AttributeTypeRepository;
use Doctrine\Common\Collections\ArrayCollection;
use Doctrine\Common\Collections\Collection;
use Doctrine\ORM\Mapping as ORM;
use JsonSerializable;

/**
 * @ORM\Entity(repositoryClass=AttributeTypeRepository::class)
 */
class AttributeType implements JsonSerializable {
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

    /**
     * @ORM\OneToMany(targetEntity=ProductAttribute::class, mappedBy="attributeType", orphanRemoval=true)
     */
    private $productAttributes;

    public function __construct() {
        $this->productAttributes = new ArrayCollection();
    }

    public function jsonSerialize() {
        $values = array_map(fn($pa) => $pa->getValue(), $this->productAttributes->getValues());
        $values = array_unique($values);
        $values = array_values($values);
        return [
                'id' => $this->getId(),
                'name' => $this->getName(),
                'values' => $values,
        ];
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

    /**
     * @return Collection|ProductAttribute[]
     */
    public function getAttributes(): Collection {
        return $this->productAttributes;
    }
}
