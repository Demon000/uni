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
     * @return JsonResponse
     */
    public function listCities() {
        $cityRepository = $this->getDoctrine()->getRepository(City::class);
        $cities = $cityRepository->findAll();
        $cities = array_map(function ($city) {
            return $city->toSerializable();
        }, $cities);
        return new JsonResponse($cities);
    }

    /**
     * @Route("/{id}", methods={"GET"}, name="get")
     * @param $id
     * @return JsonResponse
     */
    public function getCity(string $id) {
        $cityRepository = $this->getDoctrine()->getRepository(City::class);
        $city = $cityRepository->findOneBy(array(
                'id' => $id,
        ));

        $trackRepository = $this->getDoctrine()->getRepository(Track::class);
        $connections = $trackRepository->findConnectedCities($city);

        if ($city == null) {
            $response = new JsonResponse(array(
                    'error' => true,
                    'message' => 'Failed to find city',
            ));
            $response->setStatusCode(Response::HTTP_NOT_FOUND);
            return $response;
        }

        $city = $city->toSerializable();
        $connections = array_map(function ($city) {
            return $city->toSerializable();
        }, $connections);

        $city['connections'] = $connections;
        return new JsonResponse($city);
    }
}
