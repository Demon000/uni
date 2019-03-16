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

void test_products_list_first() {
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

int main() {
    ProductRepository* repository = ProductRepository__create();
    ProductService* service = ProductService__create(repository);

    test_product();
    test_products_list_first();

    ProductService__destroy(service);
    ProductRepository__destroy(repository);

    return 0;
}
