#include <assert.h>
#include <string.h>

#include "repositories/ProductRepository.h"
#include "services/ProductService.h"

void test_product() {
    Product* product = Product__create(1, 200, 20,
        "TV", "Samsung", "Infinity");

    assert(Product__get_id(product) == 1);
    assert(Product__get_price(product) == 200);
    assert(Product__get_amount(product) == 20);
    assert(strcmp(Product__get_type(product), "TV") == 0);
    assert(strcmp(Product__get_brand(product), "Samsung") == 0);
    assert(strcmp(Product__get_model(product), "Infinity") == 0);

    Product__set_price(product, 300);
    assert(Product__get_price(product) == 300);

    Product__set_amount(product, 30);
    assert(Product__get_amount(product) == 30);

    Product__destroy(product);
}

void test_products_list() {
    ProductsList* list = ProductsList__create(1);
    Product* retrieved;

    Product* first = Product__create(1, 200, 20,
        "TV", "Samsung", "Infinity");
    ProductsList__add(list, first);
    assert(ProductsList__get_length(list) == 1);

    Product* second = Product__create(2, 300, 30,
        "TV", "LG", "Fail");
    ProductsList__add(list, second);
    assert(ProductsList__get_length(list) == 2);

    retrieved = ProductsList__get(list, 0);
    assert(retrieved == first);

    ProductsList__swap(list, 0, 1);

    retrieved = ProductsList__get(list, 0);
    assert(retrieved == second);

    retrieved = ProductsList__get(list, 1);
    assert(retrieved == first);

    retrieved = ProductsList__get(list, 2);
    assert(retrieved == NULL);


    Product__destroy(second);
    Product__destroy(first);
    ProductsList__destroy(list);
}

void test_repository() {
    ProductRepository* repository = ProductRepository__create();
    ProductsList* list;
    Product* retrieved;

    Product* first = Product__create(1, 200, 20,
        "TV", "Samsung", "Infinity");
    ProductRepository__add_product(repository, first);

    Product* second = Product__create(2, 300, 30,
        "TV", "LG", "Failtinity");
    ProductRepository__add_product(repository, second);

    Product* third = Product__create(3, 500, 10,
        "TV", "Samsung", "Spectacular");
    ProductRepository__add_product(repository, third);

    retrieved = ProductRepository__get_product_by_id(repository, 2);
    assert(retrieved == second);

    retrieved = ProductRepository__get_product_by_id(repository, 4);
    assert(retrieved == NULL);

    list = ProductRepository__get_products(repository);
    assert(ProductsList__get_length(list) == 3);
    assert(ProductsList__get(list, 0) == first);
    assert(ProductsList__get(list, 1) == second);
    assert(ProductsList__get(list, 2) == third);
    ProductsList__destroy(list);

    list = ProductRepository__get_products_by_brand(repository, "Samsung");
    assert(ProductsList__get_length(list) == 2);
    assert(ProductsList__get(list, 0) == first);
    assert(ProductsList__get(list, 1) == third);
    ProductsList__destroy(list);

    list = ProductRepository__get_products_by_price(repository, 200);
    assert(ProductsList__get_length(list) == 1);
    assert(ProductsList__get(list, 0) == first);
    ProductsList__destroy(list);

    list = ProductRepository__get_products_by_amount(repository, 10);
    assert(ProductsList__get_length(list) == 1);
    assert(ProductsList__get(list, 0) == third);
    ProductsList__destroy(list);

    ProductRepository__update_product(repository, first, 350, 40);
    retrieved = ProductRepository__get_product_by_id(repository, 1);
    assert(retrieved == first);
    assert(Product__get_price(retrieved) == 350);
    assert(Product__get_amount(retrieved) == 40);

    ProductRepository__remove_product(repository, first);
    retrieved = ProductRepository__get_product_by_id(repository, 1);
    assert(retrieved == NULL);

    ProductRepository__remove_product(repository, first);

    ProductRepository__destroy(repository);
}

int main() {
    test_product();
    test_products_list();
    test_repository();

    return 0;
}
