#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct argument_t {
	pthread_cond_t cond;
	pthread_mutex_t mutex;

	int found;
	char vowel;
	char* path;
} argument_t; 

void *first_thread_fn(void *parg) {
	struct argument_t* arg = parg;
	int no_target_vowels;
	int no_vowels = 0;
	char vowel;
	FILE* in;

	in = fopen(arg->path, "r");

	fscanf(in, "%d", &no_target_vowels);

	while (fread(&vowel, 1, 1, in) == 1) {
		if (strchr("aeiou", vowel) == NULL) {
			continue;
		}

		no_vowels++;
		if (no_vowels == no_target_vowels) {
			pthread_mutex_lock(&arg->mutex);
			arg->vowel = vowel;
			arg->found = 1;
			pthread_cond_signal(&arg->cond);
			pthread_mutex_unlock(&arg->mutex);
		}
	}	

	if (no_vowels < no_target_vowels) {
		pthread_mutex_lock(&arg->mutex);
		arg->found = 1;
		pthread_cond_signal(&arg->cond);
		pthread_mutex_unlock(&arg->mutex);
	}

	fclose(in);

	return NULL;
}

void *second_thread_fn(void *parg) {
	struct argument_t* arg = parg;

	pthread_mutex_lock(&arg->mutex);
	while (arg->found == 0) {
		pthread_cond_wait(&arg->cond, &arg->mutex);
	}

	if (arg->vowel == 0) {
		printf("Couldn't find vowel.\n");
	} else {
		printf("Found vowel: %c\n", arg->vowel);
	}
	pthread_mutex_unlock(&arg->mutex);

	return NULL;
}

int main(int argc, char **argv) {
	int no_paths = argc - 1;

	struct argument_t* args = malloc(sizeof(argument_t) * no_paths);
	for (int i = 0; i < no_paths; i++) {
		struct argument_t* arg = &args[i];
		pthread_mutex_init(&arg->mutex, NULL);
		pthread_cond_init(&arg->cond, NULL);
		arg->vowel = 0;
		arg->path = argv[i + 1];
	}

	pthread_t *first_threads = malloc(sizeof(pthread_t) * no_paths);
	pthread_t *second_threads = malloc(sizeof(pthread_t) * no_paths);
	for (int i = 0; i < no_paths; i++) {
		pthread_create(&first_threads[i], NULL, first_thread_fn, &args[i]);
		pthread_create(&second_threads[i], NULL, second_thread_fn, &args[i]);
	}

	for (int i = 0; i < no_paths; i++) {
		pthread_join(first_threads[i], NULL);
		pthread_join(second_threads[i], NULL);
	}

	free(first_threads);
	free(second_threads);
	free(args);

	return 0;
}

