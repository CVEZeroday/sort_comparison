#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10

void* writeFile(void* arg)
{
  long thread_id = (long)arg;
  long start = thread_id * 1000000 + 1;
  long end = start + 1000000 - 1;

  char filename[20];
  sprintf(filename, "output_%ld.txt", thread_id);

  FILE* file = fopen(filename, "w");

  if (file == NULL) {
    printf("파일을 열 수 없습니다.\n");
    pthread_exit(NULL);
  }

  for (long i = start; i <= end; i++) {
    fprintf(file, "%ld\n", i);
  }

  fclose(file);

  pthread_exit(NULL);
}

int main()
{
  pthread_t threads[NUM_THREADS];

  for (long t = 0; t < NUM_THREADS; t++) {
    int result = pthread_create(&threads[t], NULL, writeFile, (void*)t);
    if (result != 0) {
      printf("스레드를 생성할 수 없습니다.\n");
      exit(EXIT_FAILURE);
    }
  }

  for (long t = 0; t < NUM_THREADS; t++) {
    pthread_join(threads[t], NULL);
  }

  printf("파일 생성이 완료되었습니다.\n");

  char filename[20];
  FILE* output_file = fopen("seq.txt", "w");

  if (output_file == NULL) {
    printf("파일을 열 수 없습니다.\n");
    exit(EXIT_FAILURE);
  }

  for (int t = 0; t < NUM_THREADS; t++) {
    sprintf(filename, "output_%d.txt", t);

    FILE* input_file = fopen(filename, "r");

    if (input_file == NULL) {
      printf("파일을 열 수 없습니다.\n");
      exit(EXIT_FAILURE);
    }

    char line[20];
    while (fgets(line, sizeof(line), input_file)) {
      fputs(line, output_file);
    }

    fclose(input_file);
  }

  fclose(output_file);

  system("rm ./output_*");
  printf("파일 병합이 완료되었습니다.\n");

  return 0;
}

