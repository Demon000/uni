#include "../utils/Vector.h"
#include "../entities/Product.h"
#include "../repositories/ProductRepository.h"
#include "../services/ProductService.h"

#ifndef CONSOLE_H
#define CONSOLE_H

typedef struct Console {
    ProductService* service;
} Console;

Console* Console__create(ProductService*);
void Console__destroy(Console*);

void Console__run(Console*);

#endif // CONSOLE_H
