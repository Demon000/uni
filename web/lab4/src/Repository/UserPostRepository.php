<?php

namespace App\Repository;

use App\Entity\User;
use App\Entity\UserPost;
use Doctrine\Bundle\DoctrineBundle\Repository\ServiceEntityRepository;
use Doctrine\Persistence\ManagerRegistry;

/**
 * @method UserPost|null find($id, $lockMode = null, $lockVersion = null)
 * @method UserPost|null findOneBy(array $criteria, array $orderBy = null)
 * @method UserPost[]    findAll()
 * @method UserPost[]    findBy(array $criteria, array $orderBy = null, $limit = null, $offset = null)
 */
class UserPostRepository extends ServiceEntityRepository
{
    public function __construct(ManagerRegistry $registry)
    {
        parent::__construct($registry, UserPost::class);
    }

    public function create(User $user, string $title, string $description) {
        $userPost = new UserPost();
        $userPost->setUser($user);
        $userPost->setTitle($title);
        $userPost->setDescription($description);

        $this->_em->persist($userPost);
        $this->_em->flush();

        return $userPost;
    }

    public function findForUser(User $user) {
        return $this->findBy([
                'user' => $user,
        ]);
    }

    public function findByIdForUser(User $user, int $userPostId) {
        return $this->findOneBy([
                'user' => $user,
                'id' => $userPostId,
        ]);
    }
}
