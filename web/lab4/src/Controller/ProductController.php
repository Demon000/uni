<?php

namespace App\Controller;

use App\Entity\AttributeType;
use App\Entity\Product;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\JsonResponse;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\Routing\Annotation\Route;

/**
 * @Route("/api/products", name="products_")
 */
class ProductController extends AbstractController {
    /**
     * @Route("/", methods={"GET"}, name="list")
     * @param Request $request
     * @return JsonResponse
     */
    public function listProducts(Request $request) {
        $productRepository = $this->getDoctrine()->getRepository(Product::class);
        $products = $productRepository->findAllWithAttributes($request->query);
        return $this->json($products);
    }

    /**
     * @Route("/attributes", methods={"GET"}, name="attributes")
     * @return JsonResponse
     */
    public function listAttributes() {
        $attributeTypeRepository = $this->getDoctrine()->getRepository(AttributeType::class);
        $attributesTypes = $attributeTypeRepository->findAll();
        return $this->json($attributesTypes);
    }

    /**
     * @Route("/{id}", methods={"PATCH"}, name="update")
     * @param Request $request
     * @param string $id
     * @return JsonResponse
     */
    public function updateProduct(Request $request, string $id) {
        $productRepository = $this->getDoctrine()->getRepository(Product::class);
        $body = json_decode($request->getContent(), true);

        $product = $productRepository->findOneBy([
                'id' => $id,
        ]);
        if ($product == null) {
            return $this->json([
                    'error' => true,
                    'message' => 'Failed to find product',
            ], Response::HTTP_NOT_FOUND);
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

        return $this->json($product);
    }
}
