#include "repositories/ProductRepository.h"
#include "services/ProductService.h"

int main() {
    ProductRepository* repository = ProductRepository__create();
    ProductService* service = ProductService__create(repository);

    ProductService__destroy(service);
    ProductRepository__destroy(repository);

    return 0;
}
