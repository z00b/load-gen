#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *spin_cpu(void *thread_num) {
	int *thread_id = (int *) thread_num;
	printf("starting thread number %d\n", *thread_id);
	while(1) {
		usleep(100);
	}
	return NULL;
}

int main(int argc, char **argv) {
	int thread_num;
	int thread_count = 1;
	pthread_t *threads;
	pthread_t *thread;
	if (2 == argc) {
		thread_count = atoi(argv[1]);
	}
	threads = (pthread_t *) malloc(sizeof(pthread_t) * thread_count);

	printf("thread count: %d\n", thread_count);
	for (thread_num = 0, thread = threads; thread_num < thread_count; thread_num++, thread++) {
		pthread_create(thread, NULL, spin_cpu, &thread_num);
	}
	for (thread = threads; thread - threads < thread_count; thread++) {
		pthread_join(*thread, NULL);
	}
}
