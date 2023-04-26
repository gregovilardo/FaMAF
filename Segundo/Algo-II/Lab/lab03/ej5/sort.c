/*
  @file sort.c
  @brief sort functions implementation
*/

#include "sort.h"
#include "helpers.h"
#include "player.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


bool array_is_sorted(player_t atp[], unsigned int length) {
  unsigned int i = 1u;
  while (i < length && goes_before(atp[i - 1u], atp[i])) {
    i++;
  }
  return (i == length);
}

static unsigned int partition(player_t a[], unsigned int izq,
                              unsigned int der) {
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

static void quick_sort_rec(player_t a[], unsigned int izq, unsigned int der) {
  unsigned int pivot;
  if (der > izq) {
    pivot = partition(a, izq, der);
    quick_sort_rec(a, izq, (pivot == 0u) ? 0u : pivot - 1u);
    quick_sort_rec(a, pivot + 1, der);
  }
}

void sort(player_t a[], unsigned int length) {
  quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}
