#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

void rebuild(unsigned int indexes[], char letters[], char sorted[],
             unsigned int length) {
  for (unsigned int i = 0; i < length; i++) {
    if (indexes[i] > MAX_SIZE) {
      printf("The index is too big\n");
    } else {
      sorted[indexes[i]] = letters[i];
    }
  }
}

unsigned int data_from_file(const char *path, unsigned int indexes[],
                            char letters[], unsigned int max_size) {
  FILE *file = fopen(path, "r");
  if (file != NULL) {
    unsigned int i = 0;
    while (i < max_size && !feof(file)) {
      fscanf(file, "%u %*2s %*c%c%*c ", &indexes[i], &letters[i]);
      /*     printf("%c\n", letters[i]); */
      i++;
    }
    return i;
  } else {
    printf("Cannot read file\n");
    return EXIT_FAILURE;
  }
}

static void dump(char a[], unsigned int length) {
  printf("\"");
  for (unsigned int j = 0u; j < length; j++) {
    printf("%c", a[j]);
  }
  printf("\"");
  printf("\n\n");
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Invalid path\n");
    return EXIT_FAILURE;
  }
  /*  FILE *file; */
  unsigned int indexes[MAX_SIZE];
  char letters[MAX_SIZE];
  char sorted[MAX_SIZE];
  unsigned int length = data_from_file(argv[1], indexes, letters, MAX_SIZE);
  rebuild(indexes, letters, sorted, length);
  dump(sorted, length);

  return EXIT_SUCCESS;
}
