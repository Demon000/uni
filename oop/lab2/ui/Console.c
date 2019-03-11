#include <stdio.h>
#include <stdlib.h>

#include "Console.h"

Console* Console__create(ProductService* service) {
    Console* console = malloc(sizeof(Console));

    console->service = service;
}

void Console__destroy(Console* console) {
    free(console);
}

void Console__ask_int(char* message, int* value) {
    int result;

    while (1) {
        printf("%s", message);
        result = scanf("%d", value);
        if (result == 1) {
            break;
        }

        printf("Invalid number.\n");
        while (getchar() != '\n');
    }
}

void Console__ask_str(char* message, char* str) {
    int result;

    while (1) {
        printf("%s", message);
        result = scanf("%s", str);
        if (result == 1) {
            break;
        }

        printf("Invalid string.\n");
        while (getchar() != '\n');
    }
}

void Console__print_product(Product* product) {
    printf("Id: %d, Type: %s, Brand: %s, Model: %s, "
            "Price: %d, Amount %d\n", product->id,
            product->type, product->brand, product->model,
            product->price, product->amount);
}

void Console__print_products(ProductsList* list) {
    for (int i = 0; i < list->length; i++) {
        Console__print_product(list->items[i]);
    }
}

void Console__add_product(Console* console) {
    ProductId id;
    ProductPrice price;
    ProductAmount amount;

    char type[PRODUCT_STRING_MAX_SIZE];
    char brand[PRODUCT_STRING_MAX_SIZE];
    char model[PRODUCT_STRING_MAX_SIZE];

    Console__ask_int("Id: ", &id);
    Console__ask_str("Type: ", type);
    Console__ask_str("Brand: ", brand);
    Console__ask_str("Model: ", model);
    Console__ask_int("Price: ", &price);
    Console__ask_int("Amount: ", &amount);

    Product* product = ProductService__add_product(console->service, id,
            price, amount, type, brand, model);

    printf("Added product: ");
    Console__print_product(product);
}

void Console__update_product(Console* console) {

}

void Console__delete_product(Console* console) {

}

void Console__show_products(Console* console) {
    ProductsList* list = ProductService__get_products(console->service);
    Console__print_products(list);
    ProductsList__destroy(list);
}

int Console__ask_option(Console* console) {
    int option;

    printf("Options:\n"
            "1. Add a product\n"
            "2. Update a product\n"
            "3. Delete a product\n"
            "4. Show products\n"
            "0. Exit\n");

    Console__ask_int("Option: ", &option);
    switch (option) {
    case 0:
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
    default:
        printf("Invalid option");
        break;
    }

    return option;
}

void Console__run(Console* console) {
    int result;
    while (1) {
        result = Console__ask_option(console);
    }
}
