#include <stdio.h>
#include <stdlib.h>

#include "Console.h"

Console* Console__create(ProductService* service) {
    Console* console = malloc(sizeof(Console));

    console->service = service;

    return console;

}

void Console__destroy(Console* console) {
    free(console);
}

void Console__exit(Console* console) {
    (void)(console);
    printf("Goodbye.\n");
}

#define Console__ask_number_cond(message, value, loop, condition) \
        int result; \
        while (1) { \
            printf("%s", message); \
            result = scanf("%d", value); \
            if (*value > -1 && result == 1 && condition) { \
                break; \
            } \
            printf("Invalid number.\n"); \
            while (getchar() != '\n'); \
            if (!loop) { \
                break; \
            } \
        }

void Console__ask_number_ranged(char* message, int* value, int loop,
    int min, int max) {
    Console__ask_number_cond(message, value, loop,
            *value >= min && *value <= max);
}

void Console__ask_number(char* message, int* value, int loop) {
    Console__ask_number_cond(message, value, loop, 1);
}

void Console__ask_str(char* message, char* str, int loop) {
    int result;

    while (1) {
        printf("%s", message);
        result = scanf("%s", str);
        if (result == 1) {
            break;
        }

        printf("Invalid string.\n");
        while (getchar() != '\n');

        if (!loop) {
            break;
        }
    }
}

void Console__print_product(Product* product) {
    if (!product) {
        printf("Product does not exist.\n");
        return;
    }

    printf("Id: %d, Type: %s, Brand: %s, Model: %s, "
            "Price: %d, Amount %d\n",
            Product__get_id(product),
            Product__get_type(product),
            Product__get_brand(product),
            Product__get_model(product),
            Product__get_price(product),
            Product__get_amount(product));
}

void Console__print_products(Vector* products) {
    int length = Vector__get_length(products);
    for (int i = 0; i < length; i++) {
        Product* product = Vector__get(products, i);
        Console__print_product(product);
    }
}

void Console__add_product(Console* console) {
    ProductId id;
    ProductPrice price;
    ProductAmount amount;

    char type[PRODUCT_STRING_MAX_SIZE];
    char brand[PRODUCT_STRING_MAX_SIZE];
    char model[PRODUCT_STRING_MAX_SIZE];

    Console__ask_number("Id: ", &id, 1);
    Console__ask_str("Type: ", type, 1);
    Console__ask_str("Brand: ", brand, 1);
    Console__ask_str("Model: ", model, 1);
    Console__ask_number("Price: ", &price, 1);
    Console__ask_number("Amount: ", &amount, 1);

    Product* product = ProductService__add_product(console->service, id,
            price, amount, type, brand, model);

    printf("Added product: ");
    Console__print_product(product);
}

void Console__update_product(Console* console) {
    ProductId id;
    ProductPrice price = -1;
    ProductAmount amount = -1;

    Console__ask_number("Id: ", &id, 1);
    Console__ask_number("New price (invalid to skip): ", &price, 0);
    Console__ask_number("New amount (invalid to skip): ", &amount, 0);

    Product* product = ProductService__update_product(console->service,
            id, price, amount);
    printf("Updated product: ");
    Console__print_product(product);
}

void Console__delete_product(Console* console) {
    ProductId id;
    Console__ask_number("Id: ", &id, 1);
    ProductError result = ProductService__remove_product(console->service, id);
    if (result == PRODUCT_NOT_FOUND) {
        printf("Product with Id: %d does not exist.\n", id);
    } else {
        printf("Deleted product with Id: %d.\n", id);
    }
}

void Console__show_products(Console* console) {
    Vector* products = ProductService__get_products(console->service);
    printf("Products:\n");
    Console__print_products(products);
    Vector__destroy(products);
}

void Console__ask_sort_option(Console* console) {
    ProductSortType type;
    ProductSortOrder order;
    int value;

    printf("Sort type:\n"
            "\t1. Price\n"
            "\t2. Amount\n");

    Console__ask_number_ranged("Sort type: ", &value, 1, 1, 2);
    type = value - 1;

    printf("Sort order:\n"
            "\t1. Ascending\n"
            "\t2. Descending\n");

    Console__ask_number_ranged("Sort order: ", &value, 1, 1, 2);
    order = value - 1;

    Vector* products = ProductService__get_sorted_products(console->service,
            type, order);
    printf("Sorted products:\n");
    Console__print_products(products);
    Vector__destroy(products);
}

void Console__ask_filter_option(Console* console) {
    char brand[PRODUCT_STRING_MAX_SIZE];
    ProductPrice price;
    ProductAmount amount;
    int option;

    printf("Filter by:\n"
            "\t1. Brand\n"
            "\t2. Price\n"
            "\t3. Amount\n");

    Console__ask_number_ranged("Filter by: ", &option, 1, 1, 3);

    Vector* products;
    switch (option) {
    case 1:
        Console__ask_str("Brand: ", brand, 1);
        products = ProductService__get_products_by_brand(console->service, brand);
        break;
    case 2:
        Console__ask_number("Price: ", &price, 1);
        products = ProductService__get_products_by_price(console->service, price);
        break;
    case 3:
        Console__ask_number("Amount: ", &amount, 1);
        products = ProductService__get_products_by_amount(console->service, amount);
        break;
    }

    printf("Filtered products:\n");
    Console__print_products(products);
    Vector__destroy(products);
}

int Console__ask_option(Console* console) {
    int option;

    printf("Options:\n"
            "\t1. Add a product\n"
            "\t2. Update a product\n"
            "\t3. Delete a product\n"
            "\t4. Show products\n"
            "\t5. Show products sorted by price or quantity\n"
            "\t6. Show products matching a filter\n"
            "\t0. Exit\n");

    Console__ask_number_ranged("Option: ", &option, 0, 0, 6);
    switch (option) {
    case 0:
        Console__exit(console);
        break;
    case 1:
        Console__add_product(console);
        break;
    case 2:
        Console__update_product(console);
        break;
    case 3:
        Console__delete_product(console);
        break;
    case 4:
        Console__show_products(console);
        break;
    case 5:
        Console__ask_sort_option(console);
        break;
    case 6:
        Console__ask_filter_option(console);
        break;
    }

    return option;
}

void Console__add_test_products(Console* console) {
    ProductService__add_product(console->service, 1,
            1599, 10, "TV", "Samsung", "40NU7122");
    ProductService__add_product(console->service, 2,
            899, 50, "TV", "Samsung", "32N4002");
    ProductService__add_product(console->service, 3,
            2199, 20, "TV", "Samsung", "49NU7302");

    ProductService__add_product(console->service, 4,
            899, 10, "Fridge", "Samsung", "RT25HAR4DS9");
    ProductService__add_product(console->service, 5,
            2249, 30, "Fridge", "LG", "GBB539NSQPB");
    ProductService__add_product(console->service, 6,
            1399, 100, "Fridge", "Arctic", "AF54250");
}

void Console__run(Console* console) {
    Console__add_test_products(console);

    int result = -1;
    while (result) {
        result = Console__ask_option(console);
    }
}
