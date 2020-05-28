<?php

namespace App\Repository;

use App\Entity\User;
use App\Entity\UserImage;
use Doctrine\Bundle\DoctrineBundle\Repository\ServiceEntityRepository;
use Doctrine\Persistence\ManagerRegistry;
use Ramsey\Uuid\Uuid;
use Symfony\Component\HttpFoundation\File\Exception\FileException;
use Symfony\Component\HttpFoundation\File\UploadedFile;

/**
 * @method UserImage|null find($id, $lockMode = null, $lockVersion = null)
 * @method UserImage|null findOneBy(array $criteria, array $orderBy = null)
 * @method UserImage[]    findAll()
 * @method UserImage[]    findBy(array $criteria, array $orderBy = null, $limit = null, $offset = null)
 */
class UserImageRepository extends ServiceEntityRepository
{
    const USER_IMAGE_FILE_DIRECTORY_KEY = 'USER_IMAGE_FILE_DIRECTORY';
    const USER_IMAGE_MAX_SIZE_KEY = 'USER_IMAGE_MAX_SIZE';

    private string $directory;
    private int $maxSize;

    public function __construct(ManagerRegistry $registry)
    {
        parent::__construct($registry, UserImage::class);

        $this->directory = $_ENV[$this::USER_IMAGE_FILE_DIRECTORY_KEY];
        $this->maxSize = $_ENV[$this::USER_IMAGE_MAX_SIZE_KEY];
    }

    public function getDirectory() {
        return $this->directory;
    }

    private function storeUploadedImage(UploadedFile $file)
    {
        $filename = Uuid::uuid4()->toString() . '.' . $file->guessExtension();

        if ($file->getSize() > $this->maxSize) {
            return null;
        }

        $isImage = !!getimagesize($file->getRealPath());
        if (!$isImage) {
            return null;
        }

        try {
            $file->move($this->directory, $filename);
        } catch (FileException $e) {
            return null;
        }

        return $this->directory . $filename;
    }

    public function findByIdForUser(User $user, int $userImageId) {
        return $this->findOneBy([
                'user' => $user,
                'id' => $userImageId,
        ]);
    }

    public function findForUser(User $user) {
        return $this->findBy([
                'user' => $user,
        ]);
    }

    public function create(User $user, UploadedFile $file) {
        $filename = $this->storeUploadedImage($file);
        if (!$filename) {
            return null;
        }

        $userImage = new UserImage();
        $userImage->setUser($user);
        $userImage->setPath($filename);

        $this->_em->persist($userImage);
        $this->_em->flush();

        return $userImage;
    }

    public function remove(UserImage $userImage) {
        $this->_em->remove($userImage);
        $this->_em->flush();
    }
}
