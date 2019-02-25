#include <stdio.h>

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
 * 9. Citeste un sir de numere naturale nenule terminat cu 0 si determina
 *  numarul cifrelor 0 in care se termina numarul produs al numerelor citite.
 */
int main() {
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
