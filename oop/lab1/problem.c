#include <stdio.h>
#include <stdlib.h>

/*
 * Find the number of times `number` can be divided by `n`.
 *
 * Args:
 *      number (int): The number to divide.
 *      n (int): The number to divide by.
 *
 * Returns:
 *      int: The number of times `number` can be divided by `n`.
 */
int get_number_of_ns(int number, int n) {
    int number_of_ns = 0;

    while (number % n == 0) {
        number /= n;
        number_of_ns += 1;
    }

    return number_of_ns;
}

/*
 * Find the number of zeros using the number of twos and fives in a number.
 *
 * Args:
 *      number_of_2s (int): The number of twos.
 *      number_of_5s (int): The number of fives.
 *
 * Returns:
 *      int: The number of zeros.
 */
int get_number_of_0s(int number_of_2s, int number_of_5s) {
    return number_of_2s < number_of_5s ? number_of_2s : number_of_5s;
}

/*
 * Find the number of zeros in the product of a list of numbers.
 */
void  run_number_of_0s() {
    int number;
    int number_of_5s = 0;
    int number_of_2s = 0;
    int number_of_0s;

    printf("Introduce a 0-terminated list of numbers:\n");

    while (1) {
        scanf("%d", &number);
        if (number == 0) {
            break;
        }

        number_of_2s += get_number_of_ns(number, 2);
        number_of_5s += get_number_of_ns(number, 5);
    }

    number_of_0s = get_number_of_0s(number_of_2s, number_of_5s);

    printf("The number of zeros in the product of the numbers given is %d.\n", number_of_0s);
}

struct pair {
    int first;
    int second;
};

/*
 * Find the n-th pair of twin numbers.
 *
 * Args:
 *      n (int): Obvious.
 *
 * Returns:
 *      struct pair*: A pointer to a pair of twin primes.
 */
struct pair* get_twin_primes_pair(int n) {
    struct pair* primes;
    primes = malloc(sizeof(struct pair));

    if (n == 0) {
        primes->first = 3;
        primes->second = 5;
    } else {
        primes->first = 6 * n - 1;
        primes->second = 6 * n + 1;
    }

    return primes;
}

/*
 * Free the allocated pair of twin primes.
 *
 * Args:
 *      primes (struct pair*): A pointer to a pair of twin primes.
 */
void free_twin_primes_pair(struct pair* primes) {
    free(primes);
}

/*
 * Generate the first n pairs of twin prime numbers.
 */
void run_generate_prime_pairs() {
    int n;
    int i;

    printf("Introduce the number of twin prime pairs to generate: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("The number you entered is not larger than 0.\n");
        return;
    }

    printf("The first %d pairs of twin prime numbers are:\n", n);
    for (i = 0; i < n; i++) {
        struct pair *primes = get_twin_primes_pair(i);

        printf("%d, %d\n", primes->first, primes->second);

        free_twin_primes_pair(primes);
    }
}

/*
 * Check if the given number is prime.
 *
 * Args:
 *      n (int): The number to check.
 *
 * Returns:
 *      int: 1 if the number is prime, 0 otherwise.
 */
int is_prime(int n) {
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            return 0;
        }
    }

    return 1;
}

/*
 * Decompose even number larger than 2 into the sum of 2 prime numbers.
 */
void run_decompose_even_number() {
    int n;

    printf("Introduce an even number: ");
    scanf("%d", &n);

    if (n < 3) {
        printf("The number you entered is not larger than 2.\n");
        return;
    }

    if (n % 2 != 0) {
        printf("The number you entered is not even.\n");
        return;
    }

    for (int i = 2; i <= n / 2; i++) {
        if (is_prime(i) && is_prime(n - i)) {
            printf("%d + %d = %d\n", i, n - i, n);
            break;
        }
    }
}

int main() {
    int command;

    while(1) {
        printf("1. Find the number of 0s in the product of a list of number.\n");
        printf("2. Find the first n pairs of twin prime numbers.\n");
        printf("3. Decompose an even number larger than 2 into the sum of 2 prime numbers.\n");
        printf("0. Exit.\n");
        printf("Enter a command: ");
        scanf("%d", &command);

        if (command == 0) {
            printf("Goodbye.");
            break;

        }
        /*
         * 9. Citeste un sir de numere naturale nenule terminat cu 0 si determina
         *  numarul cifrelor 0 in care se termina numarul produs al numerelor citite.
         */
        else if (command == 1) {
            run_number_of_0s();
        }
        /*
         * 15. Determina primele n perechi de numere prime gemene, unde n este un
         *  numar natural nenul dat. Doua numere prime p si q sunt gemene
         *  daca q - p = 2.
         */
        else if (command == 2) {
            run_generate_prime_pairs();
        }
        /* 14. Descompune un numar natural par, mai mare strict ca 2, intr-o suma
         *  de doua numere prime (verificarea ipotezei lui Goldbach).
         */
        else if (command == 3) {
            run_decompose_even_number();
        } else {
            printf("The command you entered is invalid.\n");
        }
    }
}
