<?php

namespace App\Entity;

use App\Repository\ProductAttributeRepository;
use Doctrine\ORM\Mapping as ORM;
use JsonSerializable;

/**
 * @ORM\Entity(repositoryClass=ProductAttributeRepository::class)
 */
class ProductAttribute implements JsonSerializable {
    /**
     * @ORM\Id()
     * @ORM\GeneratedValue()
     * @ORM\Column(type="integer")
     */
    private $id;

    /**
     * @ORM\ManyToOne(targetEntity=Product::class, inversedBy="attributes")
     * @ORM\JoinColumn(nullable=false)
     */
    private $product;

    /**
     * @ORM\ManyToOne(targetEntity=AttributeType::class, inversedBy="productAttributes")
     * @ORM\JoinColumn(nullable=false)
     */
    private ?AttributeType $attributeType;

    /**
     * @ORM\Column(type="string", length=255)
     */
    private $value;

    public function jsonSerialize() {
        return [
                'id' => $this->attributeType->getId(),
                'name' => $this->attributeType->getName(),
                'value' => $this->value,
        ];
    }

    public function getId(): ?int {
        return $this->id;
    }

    public function getProduct(): ?Product {
        return $this->product;
    }

    public function setProduct(?Product $product): self {
        $this->product = $product;

        return $this;
    }

    public function getAttributeType(): ?AttributeType {
        return $this->attributeType;
    }

    public function setAttributeType(?AttributeType $attributeType): self {
        $this->attributeType = $attributeType;

        return $this;
    }

    public function getValue(): ?string {
        return $this->value;
    }

    public function setValue(string $value): self {
        $this->value = $value;

        return $this;
    }
}
