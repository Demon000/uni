<?php

namespace App\Repository;

use App\Entity\AttributeType;
use Doctrine\Bundle\DoctrineBundle\Repository\ServiceEntityRepository;
use Doctrine\Persistence\ManagerRegistry;

/**
 * @method AttributeType|null find($id, $lockMode = null, $lockVersion = null)
 * @method AttributeType|null findOneBy(array $criteria, array $orderBy = null)
 * @method AttributeType[]    findAll()
 * @method AttributeType[]    findBy(array $criteria, array $orderBy = null, $limit = null, $offset = null)
 */
class AttributeTypeRepository extends ServiceEntityRepository {
    public function __construct(ManagerRegistry $registry) {
        parent::__construct($registry, AttributeType::class);
    }
}
