<?php

namespace App\Repository;

use App\Entity\PostComment;
use App\Entity\UserPost;
use Doctrine\Bundle\DoctrineBundle\Repository\ServiceEntityRepository;
use Doctrine\Persistence\ManagerRegistry;

/**
 * @method PostComment|null find($id, $lockMode = null, $lockVersion = null)
 * @method PostComment|null findOneBy(array $criteria, array $orderBy = null)
 * @method PostComment[]    findAll()
 * @method PostComment[]    findBy(array $criteria, array $orderBy = null, $limit = null, $offset = null)
 */
class PostCommentRepository extends ServiceEntityRepository
{
    public function __construct(ManagerRegistry $registry)
    {
        parent::__construct($registry, PostComment::class);
    }

    public function findForPost(UserPost $post) {
        return $this->findBy([
                'post' => $post,
        ]);
    }

    public function findByIdForPost(UserPost $post, int $postCommentId) {
        return $this->findOneBy([
                'post' => $post,
                'id' => $postCommentId,
        ]);
    }

    public function create(UserPost $post, string $name, string $message) {
        $postComment = new PostComment();
        $postComment->setPost($post);
        $postComment->setName($name);
        $postComment->setMessage($message);
        $postComment->setVerified(false);

        $this->_em->persist($postComment);
        $this->_em->flush();

        return $postComment;
    }

    public function verify(PostComment $postComment) {
        $postComment->setVerified(true);
        $this->_em->persist($postComment);
        $this->_em->flush();
    }
}
