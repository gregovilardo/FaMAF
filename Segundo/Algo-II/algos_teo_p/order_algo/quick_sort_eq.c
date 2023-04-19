#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
  int aux = *a;
  *a = *b;
  *b = aux;
}

int *partition(int a[], int lft, int rgt) {
  printf("Entrando a partition con lft: %d, y rgt %d\n", lft, rgt);
  int j = rgt;
  int i = lft + 1;
  int l = i;
  static int piv[2];
  piv[0] = lft;
  while (i <= j) {
    if (a[i] <= a[piv[0]]) {
      i++;
    } else if (a[j] > a[piv[0]]) {
      j--;
    } else if (a[i] > a[piv[0]] && a[j] <= a[piv[0]]) {
      swap(&a[i], &a[j]);
      j--;
      i++;
    }
    for (int i = 0; i < 10; i++) {
      printf("%d ", a[i]);
    }
    printf("\n");
  }
  piv[1] = j;
  while (l <= j) {
    if (a[l] < a[piv[0]]) {
      l++;
    } else if (a[j] == a[piv[0]]) {
      j--;
    } else if (a[l] == a[piv[0]] && a[j] < a[piv[0]]) {
      swap(&a[l], &a[j]);
      j--;
      l++;
    }
  }
  swap(&a[piv[0]], &a[j]);

  piv[0] = j;

  return piv;
}

void quick_sort_rec(int a[], int lft, int rgt, int a_len) {
  /* for (int i = 0; i < a_len; i++) {
    printf("%d ", a[i]);
  }
  printf("\n"); */
  // printf("%d\n%d\n", lft, rgt);
  int *piv;
  if (rgt > lft) {
    piv = partition(a, lft, rgt);
    quick_sort_rec(a, lft, piv[0] - 1, a_len);
    quick_sort_rec(a, piv[1] + 1, rgt, a_len);
  }
}

void quick_sort(int a[], int rgt, int a_len) {
  quick_sort_rec(a, 0, rgt, a_len);
}

int main() {

  int n;
  printf("Ingrese tamaño del array\n");
  scanf("%d", &n);
  int a[n];
  for (int i = 0; i < n; i++) {
    printf("Valor: ");
    scanf("%d", &a[i]);
  }
  int a_len = sizeof(a) / sizeof(a[0]);
  quick_sort(a, a_len - 1, a_len);
  for (int i = 0; i < a_len; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");

  return 0;
}
