<?php

namespace App\Controller;

use App\Entity\Product;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\JsonResponse;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\Routing\Annotation\Route;

/**
 * @Route("/api/products", name="products_")
 */
class ProductController extends AbstractController
{
    /**
     * @Route("/", methods={"GET"}, name="list")
     * @return JsonResponse
     */
    public function listProducts()
    {
        $productRepository = $this->getDoctrine()->getRepository(Product::class);
        $products = $productRepository->findAll();
        $products = array_map(function ($city) {
            return $city->toSerializable();
        }, $products);
        return new JsonResponse($products);
    }

    /**
     * @Route("/{id}", methods={"PATCH"}, name="update")
     * @param Request $request
     * @param string $id
     * @return JsonResponse
     */
    public function updateProduct(Request $request, string $id)
    {
        $productRepository = $this->getDoctrine()->getRepository(Product::class);
        $body = json_decode($request->getContent(), true);

        $product = $productRepository->findOneBy(array(
            'id' => $id,
        ));
        if ($product == null) {
            $response = new JsonResponse(array(
                'error' => true,
                'message' => 'Failed to find product',
            ));
            $response->setStatusCode(Response::HTTP_NOT_FOUND);
            return $response;
        }

        if (array_key_exists('name', $body)) {
            $product->setName($body['name']);
        }

        if (array_key_exists('description', $body)) {
            $product->setDescription($body['description']);
        }

        if (array_key_exists('price', $body)) {
            $product->setPrice($body['price']);
        }

        $productRepository->update($product);

        $product = $product->toSerializable();
        return new JsonResponse($product);
    }
}
