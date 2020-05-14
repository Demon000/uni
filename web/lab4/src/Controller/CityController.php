<?php

namespace App\Controller;

use App\Entity\City;
use App\Entity\Track;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\JsonResponse;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\Routing\Annotation\Route;

/**
 * @Route("/api/cities", name="cities_")
 */
class CityController extends AbstractController {
    /**
     * @Route("/", methods={"GET"}, name="list")
     */
    public function listCities() {
        $cityRepository = $this->getDoctrine()->getRepository(City::class);
        $cities = $cityRepository->findAll();
        return $this->json($cities);
    }

    /**
     * @Route("/{id}", methods={"GET"}, name="get")
     * @param $id
     * @return JsonResponse
     */
    public function getCity(string $id) {
        $cityRepository = $this->getDoctrine()->getRepository(City::class);
        $city = $cityRepository->findOneBy([
                'id' => $id,
        ]);

        $trackRepository = $this->getDoctrine()->getRepository(Track::class);
        $connections = $trackRepository->findConnectedCities($city);

        if ($city == null) {
            return $this->json([
                    'error' => true,
                    'message' => 'Failed to find city',
            ], Response::HTTP_NOT_FOUND);
        }

        $city->setConnections($connections);
        return $this->json($city);
    }
}
