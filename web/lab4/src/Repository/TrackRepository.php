<?php

namespace App\Repository;

use App\Entity\Track;
use Doctrine\Bundle\DoctrineBundle\Repository\ServiceEntityRepository;
use Doctrine\ORM\ORMException;
use Doctrine\Persistence\ManagerRegistry;

/**
 * @method Track|null find($id, $lockMode = null, $lockVersion = null)
 * @method Track|null findOneBy(array $criteria, array $orderBy = null)
 * @method Track[]    findAll()
 * @method Track[]    findBy(array $criteria, array $orderBy = null, $limit = null, $offset = null)
 */
class TrackRepository extends ServiceEntityRepository
{
    public function __construct(ManagerRegistry $registry)
    {
        parent::__construct($registry, Track::class);
    }

    public function findWithCity($city)
    {
        return $this->createQueryBuilder('track')
            ->orWhere('track.fromCity = :city')
            ->orWhere('track.toCity = :city')
            ->setParameter('city', $city)
            ->getQuery()
            ->getResult()
        ;
    }

    public function findConnectedCities($city) {
        $tracks = $this->findWithCity($city);
        return array_map(function ($track) use ($city) {
            if ($track->getFromCity() == $city) {
                return $track->getToCity();
            } else {
                return $track->getFromCity();
            }
        }, $tracks);
    }
}
