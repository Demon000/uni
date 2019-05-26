#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t global_mutex;

int global_sum = 0;
int global_uppercase_count = 0;
 
void *run_checks(void *p) {
	char *path = p;
	int uppercase_count = 0;
	int sum = 0;

	FILE* file = fopen(path, "r");
	if (file < 0) {
		return NULL;
	}

	char c;
	while (fread(&c, 1, 1, file) == 1) {
		if (c >= 'A' && c <= 'Z') {
			uppercase_count++;
		}

		if (c >= '0' && c <= '9') {
			sum += c - '0';
		}
	}

	pthread_mutex_lock(&global_mutex);
	global_uppercase_count += uppercase_count;
	global_sum += sum;
	pthread_mutex_unlock(&global_mutex);

	return NULL;
}

int main(int argc, char **argv) {
	int no_paths = argc;
	char **paths = argv;

	pthread_t *threads = malloc(sizeof(pthread_t) * no_paths);
	for (int i = 1; i < no_paths; i++) {
		pthread_create(&threads[i], NULL, run_checks, paths[i]);
	}

	for (int i = 1; i < no_paths; i++) {
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_lock(&global_mutex);
	printf("uppercase: %d\n", global_uppercase_count);
	printf("sum: %d\n", global_sum);
	pthread_mutex_unlock(&global_mutex);

	pthread_mutex_destroy(&global_mutex);

	free(threads);

	return 0;
}

