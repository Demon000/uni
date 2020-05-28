<?php

namespace App\Repository;

use App\Entity\User;
use App\Entity\UserVerification;
use DateTime;
use Doctrine\Bundle\DoctrineBundle\Repository\ServiceEntityRepository;
use Doctrine\Persistence\ManagerRegistry;
use Ramsey\Uuid\Uuid;

/**
 * @method UserVerification|null find($id, $lockMode = null, $lockVersion = null)
 * @method UserVerification|null findOneBy(array $criteria, array $orderBy = null)
 * @method UserVerification[]    findAll()
 * @method UserVerification[]    findBy(array $criteria, array $orderBy = null, $limit = null, $offset = null)
 */
class UserVerificationRepository extends ServiceEntityRepository
{
    public function __construct(ManagerRegistry $registry)
    {
        parent::__construct($registry, UserVerification::class);
    }

    public function create(User $user, DateTime $expirationDate)
    {
        $userVerification = new UserVerification();
        $userVerification->setUser($user);
        $userVerification->setExpirationDate($expirationDate);
        $userVerification->setUuid(Uuid::uuid4()->toString());

        $this->_em->persist($userVerification);
        $this->_em->flush();

        return $userVerification;
    }

    public function findByUuid(string $uuid) {
        return $this->findOneBy([
                'uuid' => $uuid,
        ]);
    }

    public function remove(UserVerification $userVerification) {
        $this->_em->remove($userVerification);
        $this->_em->flush();
    }
}
