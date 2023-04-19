#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"
#include "sort.h"
#include "sort_helpers.h"

static unsigned int partition(int a[], unsigned int izq, unsigned int der) {
  unsigned int pivot = izq;
  unsigned int j = der;
  unsigned int i = izq + 1;
  while (i <= j) {
    if (goes_before(a[i], a[pivot])) {
      i++;
    } else if (goes_before(a[pivot], a[j])) {
      j--;
    } else if (!goes_before(a[i], a[pivot]) && !goes_before(a[pivot], a[j])) {
      swap(a, i, j);
      i++;
      j--;
    }
  }
  swap(a, pivot, j);
  pivot = j;
  return pivot;
}

static void quick_sort_rec(int a[], unsigned int izq, unsigned int der) {
  int pivot;
  if (der > izq) {
    pivot = partition(a, izq, der);
    quick_sort_rec(a, izq, (pivot == 0u) ? 0u : pivot - 1u);
    quick_sort_rec(a, pivot + 1, der);
  }
}

void quick_sort(int a[], unsigned int length) {
  quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}
