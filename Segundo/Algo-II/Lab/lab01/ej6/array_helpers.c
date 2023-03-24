#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"

unsigned int array_from_file(int array[], unsigned int max_size,
                             const char *filepath) {
  // your code here!!!
  FILE *file_r = fopen(filepath, "r");
  fscanf(file_r, "%u", &max_size);
  for (unsigned int i = 0; i < max_size; i++) {
    fscanf(file_r, "%i", &array[i]);
  }
  fclose(file_r);
  return max_size;
}

void array_dump(int a[], unsigned int length) {
  // your code here!!!
  printf("[");
  for (unsigned int i = 0; i < length; i++) {
    if (i == length - 1) {
      printf(" %i", a[i]);
    } else {
      printf(" %i,", a[i]);
    }
  }
  printf("]\n");
}

bool array_is_sorted(int a[], unsigned int length) {
  unsigned int i = 0;
  bool res = true;
  while (i < length - 1 && res) {
    if (a[i] > a[i + 1]) {
      res = false;
    }
    i = i + 1;
  }
  return res;
}

void array_swap(int a[], unsigned int i, unsigned int j) {
  int tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}
