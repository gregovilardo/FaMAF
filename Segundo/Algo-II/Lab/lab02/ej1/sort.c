#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort.h"
#include "sort_helpers.h"

static void insert(int a[], unsigned int i) {
  for (unsigned int j = i; j > 0; j--)
    if (goes_before(a[j], a[j - 1])) {
      swap(a, j - 1, j);
    }
}

void insertion_sort(int a[], unsigned int length) {
  for (unsigned int i = 1u; i < length; ++i) {
    insert(a, i);
    assert(array_is_sorted(a, i));
  }
}
