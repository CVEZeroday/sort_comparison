#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define TOTAL_NUMBERS 10000000

#define NUMBERS_PER_THREAD (TOTAL_NUMBERS / NUM_THREADS)

char filename[20];

void* generate_random_numbers(void* arg) {
    int thread_id = *(int*)arg;
    int start = thread_id * NUMBERS_PER_THREAD;
    int end = start + NUMBERS_PER_THREAD;

    srand((unsigned int)time(NULL));
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        perror("Failed to open file.");
        pthread_exit(NULL);
    }

    for (int i = start; i < end; i++) {
        short random_number = rand() % 32767;
        fprintf(file, "%d\n", random_number);
    }

    fclose(file);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    
    int n;
    scanf("%d", &n);
    sprintf(filename, "random%d.txt", n);

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        int result = pthread_create(&threads[i], NULL, generate_random_numbers, &thread_ids[i]);
        if (result != 0) {
            perror("Failed to create thread.");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Random number generation completed.\n");

    return 0;
}

