#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t global_mutex;

int global_lowercase_count = 0;
int global_uppercase_count = 0;
 
void *run_checks(void *s) {
	char *string = s;
	int lowercase_count = 0;
	int uppercase_count = 0;

	for (int i = 0; i < strlen(string); i++) {
		if (string[i] >= 'a' && string[i] <= 'z') {
			lowercase_count++;
		}

		if (string[i] >= 'A' && string[i] <= 'Z') {
			uppercase_count++;
		}
	}


	pthread_mutex_lock(&global_mutex);
	global_lowercase_count += lowercase_count;
	global_uppercase_count += uppercase_count;
	pthread_mutex_unlock(&global_mutex);

	return NULL;
}

int main(int argc, char **argv) {
	int no_strings = argc;
	pthread_t *threads = malloc(sizeof(pthread_t) * no_strings);
	for (int i = 0; i < no_strings; i++) {
		pthread_create(&threads[i], NULL, run_checks, argv[i]);
	}

	for (int i = 0; i < no_strings; i++) {
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_lock(&global_mutex);
	printf("lowercase: %d\n", global_lowercase_count);
	printf("uppercase: %d\n", global_uppercase_count);
	pthread_mutex_unlock(&global_mutex);

	pthread_mutex_destroy(&global_mutex);

	free(threads);

	return 0;
}

