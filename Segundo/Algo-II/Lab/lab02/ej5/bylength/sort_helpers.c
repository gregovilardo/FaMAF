#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"
#include "fixstring.h"
#include "sort_helpers.h"

void swap(fixstring a[], unsigned int i, unsigned int j) {
  fstring_swap(a[i], a[j]);
}

bool goes_before(fixstring x, fixstring y) {
  if (fstring_length(x) <= fstring_length(y)) {
    return true;
  }
  return false;
}

bool array_is_sorted(fixstring array[], unsigned int length) {
  unsigned int i = 1;
  while (i < length && goes_before(array[i - 1], array[i])) {
    i++;
  }
  return (i >= length);
}
