#include <stdio.h>

int main() {
    int number;
    int sum = 0;

    do {
        scanf("%d", &number);
        sum += number;
    } while(number);

    printf("%d", sum);
}
