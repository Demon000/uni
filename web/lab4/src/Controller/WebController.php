<?php

namespace App\Controller;

use App\Entity\Person;
use App\Entity\PostComment;
use App\Entity\User;
use App\Entity\UserImage;
use App\Entity\UserPost;
use App\Entity\UserVerification;
use DateInterval;
use DateTime;
use Exception;
use Swift_Mailer;
use Swift_Message;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\RedirectResponse;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\HttpFoundation\Session\SessionInterface;
use Symfony\Component\Routing\Annotation\Route;
use Symfony\Component\Security\Core\Encoder\UserPasswordEncoderInterface;

class WebController extends AbstractController
{
    private SessionInterface $session;
    private UserPasswordEncoderInterface $passwordEncoder;

    public function __construct(SessionInterface $session, UserPasswordEncoderInterface $passwordEncoder) {
        $this->session = $session;
        $this->passwordEncoder = $passwordEncoder;
    }

    /**
     * @Route("/ajax_1", name="ajax_1")
     */
    public function ajax_1()
    {
        return $this->render('ajax_1.html.twig');
    }

    /**
     * @Route("/ajax_2", name="ajax_2")
     */
    public function ajax_2()
    {
        return $this->render('ajax_2.html.twig');
    }

    /**
     * @Route("/ajax_3", name="ajax_3")
     */
    public function ajax_3()
    {
        return $this->render('ajax_3.html.twig');
    }

    /**
     * @Route("/ajax_4", name="ajax_4")
     */
    public function ajax_4()
    {
        return $this->render('ajax_4.html.twig');
    }

    /**
     * @Route("/ajax_5", name="ajax_5")
     */
    public function ajax_5()
    {
        return $this->render('ajax_5.html.twig');
    }

    /**
     * @Route("/ajax_6", name="ajax_6")
     */
    public function ajax_6()
    {
        return $this->render('ajax_6.html.twig');
    }

    public function getUserRepository() {
        return $this->getDoctrine()->getRepository(User::class);
    }

    public function getUserVerificationRepository() {
        return $this->getDoctrine()->getRepository(UserVerification::class);
    }

    public function getUserImageRepository() {
        return $this->getDoctrine()->getRepository(UserImage::class);
    }

    public function getUserPostRepository() {
        return $this->getDoctrine()->getRepository(UserPost::class);
    }

    public function getPostCommentRepository() {
        return $this->getDoctrine()->getRepository(PostComment::class);
    }

    const USER_ID_KEY = 'user_id';
    public function getLoggedInUser() {
        $userId = $this->session->get($this::USER_ID_KEY);
        if (!$userId) {
            return null;
        }

        $userRepository = $this->getUserRepository();
        return $userRepository->find($userId);
    }

    public function setLoggedInUser(User $user) {
        $this->session->set($this::USER_ID_KEY, $user->getId());
    }

    public function unsetLoggedInUser() {
        $this->session->remove($this::USER_ID_KEY);
    }

    public function findUser(string $email, string $password) {
        $userRepository = $this->getUserRepository();
        $user = $userRepository->findOneBy([
                'email' => $email,
                'verified' => true,
        ]);

        if (!$user) {
            return null;
        }

        $isPasswordValid = $this->passwordEncoder->isPasswordValid($user, $password);
        if (!$isPasswordValid) {
            return null;
        }

        return $user;
    }

    /**
     * @Route("/php_2", name="php_2")
     * @param Request $request
     */
    public function php_2(Request $request)
    {
        $available_entries = [3, 5, 10];
        $default_entries = 3;

        $entries = $request->query->getInt('entries', $default_entries);
        $page = $request->query->getInt('page', 0);

        if (!in_array($entries, $available_entries)) {
            $entries = $default_entries;
        }

        $personRepository = $this->getDoctrine()->getRepository(Person::class);
        $people = $personRepository->findPaginated($page, $entries);
        $count = $personRepository->count([]);
        $before = min($page * $entries, $count);
        $after = max($count - ($page + 1) * $entries, 0);

        return $this->render('php_2.html.twig', [
                'people' => $people,
                'before' => $before,
                'after' => $after,
                'entries' => $entries,
                'available_entries' => $available_entries,
                'page' => $page,
        ]);
    }

    /**
     * @Route("/php_4", methods={"GET"}, name="php_4")
     */
    public function php_4()
    {
        $user = $this->getLoggedInUser();
        if ($user) {
            return $this->render('php_4/protected.html.twig', [
                    'user' => $user,
            ]);
        } else {
            return $this->render('php_4/unprotected.html.twig');
        }
    }

    public function renderRegistrationFailed($e) {
        return $this->render('php_4/registration_failed.html.twig', [
                'error' => $e,
        ]);
    }

    const FROM_MAIL_KEY = 'FROM_MAIL';
    public function sendVerificationEmail(Swift_Mailer $mailer, User $user) {
        $userVerificationRepository = $this->getUserVerificationRepository();
        $expirationDate = new DateTime();
        $expirationDate->add(new DateInterval('P1D'));
        $userVerification = $userVerificationRepository->create($user, $expirationDate);

        $verificationEmail = (new Swift_Message('Verify your email'))
                ->setFrom($_ENV[$this::FROM_MAIL_KEY])
                ->setTo($user->getEmail())
                ->setBody(
                        $this->renderView('php_4/verification_email.html.twig', [
                                'user_verification_uuid' => $userVerification->getUuid(),
                        ]),
                        'text/html'
                );

        $mailer->send($verificationEmail);
    }

    /**
     * @Route("/php_4/register", methods={"POST"}, name="php_4_register")
     * @param Request $request
     * @param Swift_Mailer $mailer
     * @return Response
     */
    public function php_4_register(Request $request, Swift_Mailer $mailer)
    {
        $user = $this->getLoggedInUser();
        if ($user) {
            return $this->redirectToRoute('php_4');
        }

        $email = $request->request->get('email');
        $password = $request->request->get('password');

        if (empty($email) || empty($password)) {
            return $this->renderRegistrationFailed('Email or password empty');
        }

        $user = new User();
        $encodedPassword = $this->passwordEncoder->encodePassword($user, $password);

        $user->setEmail($email);
        $user->setPassword($encodedPassword);
        $user->setVerified(false);

        $userRepository = $this->getUserRepository();
        try {
            $userRepository->save($user);
        } catch (Exception $e) {
            return $this->renderRegistrationFailed('Failed to create user');
        }

        try {
            $this->sendVerificationEmail($mailer, $user);
        } catch (Exception $e) {
            return $this->renderRegistrationFailed('Failed to send verification email');
        }

        return $this->render('php_4/registration_successful.html.twig');
    }

    public function renderVerificationFailed($e) {
        return $this->render('php_4/verification_failed.html.twig', [
                'error' => $e,
        ]);
    }

    /**
     * @Route("/php_4/verify_email", methods={"GET"}, name="php_4_verify_email")
     * @param Request $request
     * @return Response
     */
    public function php_4_verify_email(Request $request)
    {
        $user = $this->getLoggedInUser();
        if ($user) {
            return $this->redirectToRoute('php_4');
        }

        $userVerificationUuid = $request->query->get('user_verification_uuid');
        if (empty($userVerificationUuid)) {
            return $this->renderVerificationFailed('User verification uuid not found');
        }

        $userVerificationRepository = $this->getUserVerificationRepository();
        $userVerification = $userVerificationRepository->findByUuid($userVerificationUuid);
        if (!$userVerification) {
            return $this->renderVerificationFailed('User verification not found');
        }

        $userRepository = $this->getUserRepository();
        $user = $userVerification->getUser();
        $user->setVerified(true);
        $userRepository->save($user);

        $userVerificationRepository->remove($userVerification);

        $this->setLoggedInUser($user);

        return $this->redirectToRoute('php_4');
    }

    public function renderLoginFailed($e) {
        return $this->render('php_4/login_failed.html.twig', [
                'error' => $e,
        ]);
    }

    /**
     * @Route("/php_4/login", methods={"POST"}, name="php_4_login")
     * @param Request $request
     * @return RedirectResponse|Response
     */
    public function php_4_login(Request $request)
    {
        $user = $this->getLoggedInUser();
        if ($user) {
            return $this->redirectToRoute('php_4');
        }

        $email = $request->request->get('email');
        $password = $request->request->get('password');
        $user = $this->findUser($email, $password);
        if (!$user) {
            return $this->renderLoginFailed('User does not exist');
        }

        $this->setLoggedInUser($user);

        return $this->redirectToRoute('php_4');
    }

    /**
     * @Route("/php_4/logout", methods={"GET"}, name="php_4_logout")
     * @return RedirectResponse|Response
     */
    public function php_4_logout()
    {
        $this->unsetLoggedInUser();
        return $this->redirectToRoute('php_4');
    }

    /**
     * @Route("/php_5/user/{viewedUserId}", methods={"GET"}, name="php_5_user",
     *     defaults={"viewedUserId"=null})
     * @param int|null $viewedUserId
     * @return RedirectResponse|Response
     */
    public function php_5_user(?int $viewedUserId)
    {
        $user = $this->getLoggedInUser();
        if (!$user) {
            return $this->redirectToRoute('php_4');
        }

        $userRepository = $this->getUserRepository();
        $userImageRepository = $this->getUserImageRepository();
        $userPostRepository = $this->getUserPostRepository();

        if ($viewedUserId) {
            $viewedUser = $userRepository->find($viewedUserId);
        } else {
            $viewedUser = null;
        }

        if (!$viewedUser) {
            $viewedUser = $user;
        }

        $images = $userImageRepository->findForUser($viewedUser);
        $users = $userRepository->findAll();
        $posts = $userPostRepository->findForUser($viewedUser);

        return $this->render('php_5/user.html.twig', [
                'user' => $user,
                'viewed_user' => $viewedUser,
                'users' => $users,
                'user_images' => $images,
                'user_posts' => $posts,
        ]);
    }

    public function renderImageCreateFailed($e) {
        return $this->render('php_5/user_images_create_failed.html.twig', [
                'error' => $e,
        ]);
    }

    /**
     * @Route("/php_5/user/images", methods={"POST"}, name="php_5_user_images_create")
     * @param Request $request
     * @return RedirectResponse|Response
     */
    public function php_5_user_images_create(Request $request)
    {
        $user = $this->getLoggedInUser();
        if (!$user) {
            return $this->redirectToRoute('php_4');
        }

        $file = $request->files->get('image');
        if (!$file) {
            return $this->renderImageCreateFailed('Image failed to send');
        }

        $userImageRepository = $this->getUserImageRepository();
        $userImage = $userImageRepository->create($user, $file);
        if (!$userImage) {
            return $this->renderImageCreateFailed('Image failed to create');
        }

        return $this->redirectToRoute('php_5_user');
    }

    public function renderImageDeleteFailed($e) {
        return $this->render('php_5/user_images_delete_failed.html.twig', [
                'error' => $e,
        ]);
    }

    /**
     * @Route("/php_5/user/images/{userImageId}/delete", methods={"GET"}, name="php_5_user_images_delete")
     * @param int $userImageId
     * @return RedirectResponse|Response
     */
    public function php_5_user_images_delete(int $userImageId)
    {
        $user = $this->getLoggedInUser();
        if (!$user) {
            return $this->redirectToRoute('php_4');
        }

        $userImageRepository = $this->getUserImageRepository();
        $userImage = $userImageRepository->findByIdForUser($user, $userImageId);
        if (!$userImage) {
            return $this->renderImageDeleteFailed('Failed to find image');
        }

        try {
            $userImageRepository->remove($userImage);
        } catch (Exception $e) {
            return $this->renderImageDeleteFailed('Failed to delete image');
        }

        return $this->redirectToRoute('php_5_user');
    }

    public function renderPostCreateFailed($e) {
        return $this->render('php_6/user_posts_create_failed.html.twig', [
                'error' => $e,
        ]);
    }

    /**
     * @Route("/php_6/user/posts", methods={"POST"}, name="php_6_user_posts_create")
     * @param Request $request
     * @return RedirectResponse|Response
     */
    public function php_6_user_posts_create(Request $request)
    {
        $user = $this->getLoggedInUser();
        if (!$user) {
            return $this->redirectToRoute('php_4');
        }

        $title = $request->request->get('title');
        $description = $request->request->get('description');

        if (empty($title) || empty($description)) {
            return $this->renderPostCreateFailed('Title or description empty');
        }

        $userPostRepository = $this->getUserPostRepository();
        $userPostRepository->create($user, $title, $description);

        return $this->redirectToRoute('php_5_user');
    }

    public function renderPostGetFailed($e) {
        return $this->render('php_6/user_post_get_failed.html.twig', [
                'error' => $e,
        ]);
    }

    /**
     * @Route("/php_6/posts/{userPostId}", methods={"GET"}, name="php_6_post_get")
     * @param int $userPostId
     * @return RedirectResponse|Response
     */
    public function php_6_post_get(int $userPostId)
    {
        $user = $this->getLoggedInUser();
        $userPostRepository = $this->getUserPostRepository();
        $postCommentRepository = $this->getPostCommentRepository();

        $userPost = $userPostRepository->findOneById($userPostId);
        if (!$userPost) {
            return $this->renderPostGetFailed('Failed to find post');
        }

        $comments = $postCommentRepository->findForPost($userPost);

        return $this->render('php_6/user_post.html.twig', [
                'user' => $user,
                'user_post' => $userPost,
                'post_comments' => $comments,
        ]);
    }

    public function renderPostCommentsCreateFailed($e) {
        return $this->render('php_6/user_post_comments_create_failed.html.twig', [
                'error' => $e,
        ]);
    }

    /**
     * @Route("/php_6/posts/{userPostId}/comments", methods={"POST"}, name="php_6_post_comments_create")
     * @param Request $request
     * @param int $userPostId
     * @return RedirectResponse|Response
     */
    public function php_6_post_comments_create(Request $request, int $userPostId)
    {
        $userPostRepository = $this->getUserPostRepository();
        $userPost = $userPostRepository->findOneById($userPostId);
        if (!$userPost) {
            return $this->renderPostCommentsCreateFailed('Failed to find post');
        }

        $name = $request->request->get('name');
        $message = $request->request->get('message');

        if (empty($name) || empty($message)) {
            return $this->renderPostCommentsCreateFailed('Name or message empty');
        }

        $postCommentRepository = $this->getPostCommentRepository();
        $postCommentRepository->create($userPost, $name, $message);

        return $this->redirectToRoute('php_6_post_get', [
                'userPostId' => $userPostId,
        ]);
    }

    public function renderPostCommentVerifyFailed($e) {
        return $this->render('php_6/user_post_comment_verify_failed.html.twig', [
                'error' => $e,
        ]);
    }

    /**
     * @Route("/php_6/posts/{userPostId}/comments/{postCommentId}/verify", methods={"GET"}, name="php_6_post_comment_verify")
     * @param Request $request
     * @param int $userPostId
     * @param int $postCommentId
     * @return RedirectResponse|Response
     */
    public function php_6_post_comment_verify(Request $request, int $userPostId, int $postCommentId)
    {
        $user = $this->getLoggedInUser();
        if (!$user) {
            return $this->redirectToRoute('php_4');
        }

        $userPostRepository = $this->getUserPostRepository();
        $userPost = $userPostRepository->findByIdForUser($user, $userPostId);
        if (!$userPost) {
            return $this->renderPostCommentVerifyFailed('Failed to find post');
        }

        $postCommentRepository = $this->getPostCommentRepository();
        $postComment = $postCommentRepository->findByIdForPost($userPost, $postCommentId);
        if (!$postComment) {
            return $this->renderPostCommentVerifyFailed('Failed to find post comment');
        }

        $postCommentRepository->verify($postComment);

        return $this->redirectToRoute('php_6_post_get', [
                'userPostId' => $userPostId,
        ]);
    }
}
