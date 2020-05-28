<?php

namespace App\Repository;

use App\Entity\Product;
use Doctrine\Bundle\DoctrineBundle\Repository\ServiceEntityRepository;
use Doctrine\ORM\ORMException;
use Doctrine\Persistence\ManagerRegistry;

/**
 * @method Product|null find($id, $lockMode = null, $lockVersion = null)
 * @method Product|null findOneBy(array $criteria, array $orderBy = null)
 * @method Product[]    findAll()
 * @method Product[]    findBy(array $criteria, array $orderBy = null, $limit = null, $offset = null)
 */
class ProductRepository extends ServiceEntityRepository {
    public function __construct(ManagerRegistry $registry) {
        parent::__construct($registry, Product::class);
    }

    /**
     *
     * @param Product $product
     * @throws ORMException
     */
    public function update(Product $product) {
        $this->_em->persist($product);
        $this->_em->flush();
    }

    public function findAllWithAttributes($attributes) {
        $qb = $this->createQueryBuilder('product')
            ->innerJoin('product.attributes', 'productAttribute')
            ->innerJoin('productAttribute.attributeType', 'attributeType');

        $index = 0;
        foreach ($attributes as $attributeName => $attributeValue) {
            $attributeNameParameter = sprintf('attributeName%d', $index);
            $attributeValueParameter = sprintf('attributeValue%d', $index);
            $qb->orWhere(sprintf('attributeType.name = :%s and productAttribute.value = :%s',
                    $attributeNameParameter, $attributeValueParameter));
            $qb->setParameter($attributeNameParameter, $attributeName);
            $qb->setParameter($attributeValueParameter, $attributeValue);
            $index++;
        }

        if ($index != 0) {
            $qb->groupBy('product.id');
            $qb->having('count(distinct attributeType.id) = :numberOfFilters');
            $qb->setParameter('numberOfFilters', $index);
        }

        return $qb->getQuery()
                ->getResult();
    }
}
