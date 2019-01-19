#include <stdio.h>

int add_char_to_number(int, char);

int from_binary(char number_in_binary[]) {
	int index = 0;
	int number = 0;
	char c;

	while (1) {
		c = number_in_binary[index];
		if (c == '\0') {
			break;
		}

		number = add_char_to_number(number, c);
		if (number == -1) {
			break;
		}

		index++;
	}

	return number;
}

/*
 * Se citeste de la tastatura un sir de mai multe numere in baza 2.
 * Sa se afiseze aceste numere in baza 16.
 */

int main() {
	int numbers[255] = {0};
	int numbers_read = 0;
	char number_in_binary[32];
	int number;

	printf("Enter your binary numbers:\n");
	printf("Enter an invalid number to stop.\n");

	while (1) {
		scanf("%s", number_in_binary);

		number = from_binary(number_in_binary);
		if (number == -1) {
			break;
		}

		numbers[numbers_read] = number;
		numbers_read++;
	}

	printf("Your numbers in hex are:\n");

	int index;
	for (index = 0; index < numbers_read; index++) {
		int number = numbers[index];
		printf("0x%X\n", number);
	}

	return 0;
	
}