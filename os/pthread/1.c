#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t global_mutex;

int global_three_count = 0;
int global_four_count = 0;
int global_five_count = 0;

void *run_checks(void *number_pointer) {
	int number = *(int *)number_pointer;
	int three_count = 0;
	int four_count = 0;
	int five_count = 0;

	if (number % 3 == 0) {
		three_count = 1;
	}

	if (number % 4 == 0) {
		four_count = 1;
	}

	if (number % 5 == 0) {
		five_count = 1;
	}

	pthread_mutex_lock(&global_mutex);
	global_three_count += three_count;
	global_four_count += four_count;
	global_five_count += five_count;
	pthread_mutex_unlock(&global_mutex);

	return NULL;
}

int main() {
	int no_numbers;
	printf("Number of numbers: ");
	scanf("%d", &no_numbers);

	printf("%d numbers: ", no_numbers);
	int *numbers = malloc(sizeof(int) * no_numbers);
	for (int i = 0; i < no_numbers; i++) {
		scanf("%d", &numbers[i]);
	}

	pthread_t *threads = malloc(sizeof(pthread_t) * no_numbers);
	for (int i = 0; i < no_numbers; i++) {
		pthread_create(&threads[i], NULL, run_checks, &numbers[i]);
	}

	for (int i = 0; i < no_numbers; i++) {
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_lock(&global_mutex);
	printf("%3: %d\n", global_three_count);
	printf("%4: %d\n", global_four_count);
	printf("%5: %d\n", global_five_count);
	pthread_mutex_unlock(&global_mutex);

	pthread_mutex_destroy(&global_mutex);

	free(threads);
	free(numbers);

	return 0;
}

