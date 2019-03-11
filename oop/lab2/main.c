#include "repositories/ProductRepository.h"
#include "services/ProductService.h"
#include "ui/Console.h"

int main() {
    ProductRepository* repository = ProductRepository__create();
    ProductService* service = ProductService__create(repository);

    Console__run();

    ProductService__destroy(service);
    ProductRepository__destroy(repository);

    return 0;
}