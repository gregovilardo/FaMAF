#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/**
 * Find maximum between two numbers.
 */
int max(int num1, int num2) { return (num1 > num2) ? num1 : num2; }

/**
 * Find minimum between two numbers.
 */
int min(int num1, int num2) { return (num1 > num2) ? num2 : num1; }

void swap(int *a, int *b) {
  int aux = *a;
  *a = *b;
  *b = aux;
}

int partition(int a[], int lft, int rgt) {
  printf("Entrando a partition con lft: %d, y rgt %d\n", lft, rgt);
  int j = rgt;
  int i = lft+1;
  int mid = (lft + rgt) / 2;
  int piv = lft;
  int valor_intermedio =
      max(max(min(a[lft], a[mid]), min(a[mid], a[rgt])), min(a[lft], a[rgt]));
  if (a[rgt] == valor_intermedio) {
    swap(&a[lft], &a[rgt]);
  } else if (a[mid] == valor_intermedio) {
    swap(&a[lft], &a[mid]);
  }

  while (i <= j) {
    if (a[i] <= a[piv]) {
      i++;
    }
    else if (a[j] >= a[piv]) {
      j--;
    }
    else if (a[i] > a[piv] && a[j] < a[piv]) {
      swap(&a[i], &a[j]);
      j--;
      i++;
    }
  }

  swap(&a[j], &a[piv]);
  return piv = j;
}

void quick_sort_rec(int a[], int lft, int rgt, int a_len) {
  // for (int i = 0; i < a_len; i++) {
  //   printf("%d ", a[i]);
  // }
  // printf("\n");
  // printf("%d\n%d\n", lft, rgt);
  int piv;
  if (rgt > lft) {
    piv = partition(a, lft, rgt);
    quick_sort_rec(a, lft, piv - 1, a_len);
    quick_sort_rec(a, piv + 1, rgt, a_len);
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
