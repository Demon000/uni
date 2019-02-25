#include <stdio.h>
#include <stdlib.h>

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
 * 15. Determina primele n perechi de numere prime gemene, unde n este un
 *  numar natural nenul dat. Doua numere prime p si q sunt gemene
 *  daca q-p = 2.
 */
int main() {
    int n;
    int i;

    printf("Introduce the number of cousin prime pairs to generate: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        struct pair *primes = get_nth_cousin_primes_pair(i);

        printf("%d, %d\n", primes->first, primes->second);

        free_nth_cousin_primes_pair(primes);
    }
}
