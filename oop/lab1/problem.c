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


/*
 * Find the n-th uneven number.
 *
 * Args:
 *      n (int): Obvious.
 *
 * Returns:
 *      int: The the n-th uneven number.
 */
int get_nth_uneven(int n) {
    return 2 * n - 1;
}

struct pair {
    int first;
    int second;
};

/*
 * Find the n-th pair of cousin numbers.
 *
 * Args:
 *      n (int): Obvious.
 *
 * Returns:
 *      struct pair*: A pointer to a pair of cousin primes.
 */
struct pair* get_nth_cousin_primes_pair(int n) {
    struct pair* primes;
    primes = malloc(sizeof(struct pair));

    primes->first = get_nth_uneven(n);
    primes->second = get_nth_uneven(n + 1);

    return primes;
}

/*
 * Free the allocated pair of cousin primes.
 *
 * Args:
 *      primes (struct pair*): A pointer to a pair of cousin primes.
 */
void free_nth_cousin_primes_pair(struct pair* primes) {
    free(primes);
}

/*
 * Generate the first n pairs of cousin prime numbers.
 */
void run_generate_prime_pairs() {
    int n;
    int i;

    printf("Introduce the number of cousin prime pairs to generate: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("The number you entered is not larger than 0.\n");
        return;
    }

    printf("The first %d pairs of cousin prime numbers are:\n", n);
    for (i = 1; i <= n; i++) {
        struct pair *primes = get_nth_cousin_primes_pair(i);

        printf("%d, %d\n", primes->first, primes->second);

        free_nth_cousin_primes_pair(primes);
    }
}

int main() {
    int command;

    while(1) {
        printf("1. Find the number of 0s in the product of a list of number.\n");
        printf("2. Find the first n pairs of cousin prime numbers.\n");
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
         *  daca q-p = 2.
         */
        else if (command == 2) {
            run_generate_prime_pairs();
        } else {
            printf("The command you entered is invalid.\n");
        }
    }
}
