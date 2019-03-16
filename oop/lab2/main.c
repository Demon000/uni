#include "repositories/ProductRepository.h"
#include "services/ProductService.h"
#include "ui/Console.h"

int main() {
    ProductRepository* repository = ProductRepository__create();
    ProductService* service = ProductService__create(repository);

    Console* console = Console__create(service);
    Console__run(console);
    Console__destroy(console);

    ProductService__destroy(service);
    ProductRepository__destroy(repository);

    return 0;
}
