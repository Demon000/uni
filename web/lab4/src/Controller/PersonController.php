<?php

namespace App\Controller;

use App\Entity\Person;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\JsonResponse;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\Routing\Annotation\Route;

/**
 * @Route("/api/people", name="people_")
 */
class PersonController extends AbstractController {
    /**
     * @Route("/", methods={"GET"}, name="list")
     * @param Request $request
     * @return JsonResponse
     */
    public function listPeople(Request $request) {
        $page = $request->query->get('page');
        $entries = 3;

        $personRepository = $this->getDoctrine()->getRepository(Person::class);
        $people = $personRepository->findPaginated($page, $entries);
        $people = array_map(function ($person) {
            return $person->toSerializable();
        }, $people);
        $count = $personRepository->count(array());
        $before = min($page * $entries, $count);
        $after = max($count - ($page + 1) * $entries, 0);

        return new JsonResponse(array(
                'count' => $count,
                'before' => $before,
                'after' => $after,
                'data' => $people,
        ));
    }
}
